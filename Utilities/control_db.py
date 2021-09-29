import inspect
import re
import pprint

class GRAND:
    def __init__(self, conn, host, user, password, db, charset='utf8'):
        # connect 시 필요한 변수
        # self.host = host
        # self.user = user
        # self.password = password
        # self.charset= charset
        self.db = db
        # connect 함수 ex) pymysql.connect
        self.conn_func = conn
        # connect
        self.conn = self.conn_func(
                    host = host,
                    user = user,
                    password = password,
                    db = db,
                    charset = charset
            )
        # table 및 describe 정보
        # 동작 방식 변경에 의해 두 변수가 필요 없어짐.
        # self.tables = None
        # self.desc = None
        
    def __del__(self, ):
        self.conn.close()

    # 함수 목록 및 이름 반환,
    def __func_call__(self, ):
        func_attr = self.__dict__
    
        # 함수 목록 넣기
        _func_call_ = [self.__getattribute__(func)
                    for func in self.__dir__()
                    if '__' not in func # 단점 : '__'를 함수에 사용하지 못함
                    and func not in func_attr
        ]
        # 함수 넘버링
        func_call = {num+1 : func for num, func in enumerate(_func_call_)}
        # 함수 이름
        func_name = {num+1 : func.__name__ for num, func in enumerate(_func_call_)}

        return func_call, func_name

    # db 재선택
    def use_db(self, db=None, print_=True):
        if db is None :
            db = input('plz input db name\n')
        self.db = db
        with self.conn.cursor() as curs:
            sql = f'use {self.db}'
            curs.execute(sql)
            print(f'change to use {self.db}')

    # db 목록 열람
    def show_databases(self, print_=True):
        with self.conn.cursor() as curs:
            sql = 'show databases'
            curs.execute(sql)
            if print_:
                print(curs.fetchall())

    # db 안의 테이블 목록 보기
    def show_tables(self, ):
        sql = f'show tables from {self.db}'
        with self.conn.cursor() as curs:
            curs.execute(sql)
            result = curs.fetchall()
            print(result)
            # self.tables = curs.fetchall()
            # if print_:
            #     print(self.tables)
    # 테이블 형식 보기
    # 기존에는 변수에 desc 값들을 dict 형태로 테이블마다 넣어서 했음
    # 제약조건 확인과 같은 특별한 테이블은 show table에 나타나지 않으므로,
    # 동작 방식 변경. 그에 따라, print_=True와 같은 변수는 필요 없어진것 같음.
    def desc_tables(self, table=None, ):
        # if self.tables is None:
        #     self.show_tables(print_=False)

        with self.conn.cursor() as curs:
            if table is None :
                self.show_tables()
                table = input('plz input table name\n')
            
            # sqls = (f'desc {table[0]}' for table in self.tables)
            # self.desc ={self.tables[num][0] : curs.fetchall() \
            #             for num, desc in enumerate(map(curs.execute, sqls))}
            # 테이블 리스트화
            table = re.split(', | ', table)
            table = [tb for tb in table if len(tb) > 3]

            sql = (f'desc {tb}' for tb in table)
            result = [curs.fetchall() for _ in map(curs.execute, sql)]

            print(f'##### {table} #####')
            try:
                # pprint.pprint(self.desc[table])
                pprint.pprint(result)
            except:
                raise Exception(f'There is no table name like "{table}"')
    
    # get table, columns, args values for DML
    def __get_values__(self, args=True, where=False):
        # table 목록 보여줌
        self.show_tables()
        table = input('plz input table name\n')
        # table describe 보여줌
        self.desc_tables(table=table)

        columns = input('plz input column names using comma\n')

        # args가 필요하다면
        if args :
            # 조건문이 필요하다면
            if where :
                values = re.split(', | ', input('plz input values using comma or spacebar\n'))
                # values = input('plz input values using comma\n').split(',')
                condition = input('plz input condition\n')

                return table, columns, values, condition
            # 조건문이 필요하지 않다면
            else:
                values = re.split(', | ', input('plz input values using comma or spacebar\n'))
                return table, columns, values
        # args가 필요하지 않다면
        else:
            # 조건문이 필요하다면
            if where :
                condition = input('plz input condition\n')
                return table, columns, condition
            # 조건문이 필요하지 않다면
            else:
                return table, columns
    
class DDL(GRAND):
    def create(self, many_execute=False, ):
        pass

    def alter(self, sql=None, add=True, delete=True, primary_key=False):
        with self.conn.cursor() as curs:
            if sql is None:
                table, column, constraint_name, condition = self.__get_values__(args=True, where=True)
                if add:
                    # 제약조건 추가
                    if primary_key:
                        # primary key
                        sql = f"ALTER TABLE {table} ADD CONSTRAINT {constraint_name} PRIMARY KEY {column}"
                    else:                        
                        # foreign key
                        mother_table = input('plz input mother table name\n')
                        sql = f"ALTER TABLE {table} ADD CONSTRAINT {constraint_name} FOREIGN KEY({column}) REFERENCES {mother_table}({column}) ON {condition} CASCADE"
                else:
                    # 제약조건 삭제
                    if primary_key:
                        # primary key
                        sql = f"ALTER TABLE {table} DROP CONSTRAINT {constraint_name}"
                    else:
                        # foreign key
                        sql = f"ALTER TABLE {table} DROP FOREIGN KEY {constraint_name}"
            curs.execute(sql)
            self.conn.commit()
            print('alter done!')

    def drop(self, ):
        pass
    def rename(self, ):
        pass
    def comment(self, ):
        pass
    def truncate(self, ):
        pass

class DML(GRAND):
    def select(self, table=None, sql=None, many_execute=False, ):
        with self.conn.cursor() as curs:
            # 다중 select 아닐 떄
            if not many_execute:
                # table 값이 있으면
                if table is not None:
                    sql = f"SELECT * from {table}"
                # table 값도 없고, sql 값도 없으면
                elif sql is None:
                    table, columns, condition = self.__get_values__(args=False, where=True)
                    sql = f"SELECT {columns} from {table} {condition}"

                curs.execute(sql)
            else:
                if table is not None:
                    sql = f"SELECT * from {table}"
                elif sql is None:
                    table, columns, condition = self.__get_values__(args=False, where=True)
                    sql = f"SELECT {columns} from {table} {condition}"

                curs.executemany(sql)

            result = curs.fetchall()
            print(result)
            print(curs.rowcount, 'rows selected')
            return result
                    
    def insert(self, sql=None, many_execute=False, file_path=None, data=None):
        with self.conn.cursor() as curs:
            if not many_execute:
                if sql is None:
                    table, columns, values = self.__get_values__(args=True)
                    sql = f"INSERT INTO {table} ({columns}) VALUES {tuple(values)}"
                curs.execute(sql)
            else:
                if sql is None:
                    table, columns = self.__get_values__(args=False)
                    if data is None:
                        # value에 넣을 데이터 값을 파일로 읽음.
                        if file_path is None:
                            file_path = input('plz input file_path for values\n')
                        # txt, csv냐에 따라 다르게 읽을 것이므로 추후 수정 필요
                        with open(file_path, 'r') as f:
                            data = f.read().split()

                    sql = (f"INSERT INTO {table} ({columns}) VALUES {values}" for values in data)
                    # sql = f'INSERT INTO {table} ({columns}) VALUES(%s, %s)'
                    # val = [(1, 2), (3, 4) ...]
                    # curs.executemany(sql)
                    # sql문 하나씩 execute에 넘기기
                    for rowcount, _ in enumerate(map(curs.execute, sql)):
                        pass
                else:
                    # sql = (sql, val)이 되어야 함.
                    curs.executemany(sql)

            self.conn.commit()
            print(rowcount, 'rows inserted and commited')
            print('insert done!')

    def delete(self, sql=None, many_execute=False, file_path=None, data=None):
        with self.conn.cursor() as curs:
            if not many_execute:
                if sql is None:
                    table, columns, values = self.__get_values__(args=True)
                    sql = (f"DELETE FROM {table} WHERE {columns} in ('{value}')" for value in values)
                    for rowcount, _ in enumerate(map(curs.execute, sql)):
                        pass
            else:
                if sql is None:
                    table, columns = self.__get_values__(args=False)
                    if data is None:
                        # value에 넣을 데이터 값을 파일로 읽음.
                        if file_path is None:
                            file_path = input('plz input file_path for values\n')
                        # txt, csv냐에 따라 다르게 읽을 것이므로 추후 수정 필요
                        with open(file_path, 'r') as f:
                            data = f.read().split()

                    sql = (f"DELETE FROM {table} WHERE {columns} in ('{values}')" for values in data)
                    
                    # sql문 하나씩 execute에 넘기기
                    for rowcount, _ in enumerate(map(curs.execute, sql)):
                        pass
                else:
                    # sql = (sql, val)이 되어야 함.
                    curs.executemany(sql)

            self.conn.commit()
            print(rowcount, 'rows deleted and commited')
            print('delete done!')

    def update(self, ):
        pass
    def merge(self, ):
        pass
    def call(self, ):
        pass
    def explain_plan(self, ):
        pass
    def lock_table(self, ):
        pass

class DCL(GRAND):
    def grant(self, ):
        pass
    def revoke(self, ):
        pass

# 아마 tcl은 안하지 않을까?
class TCL(GRAND):
    def commit(self, ):
        pass
    def rollback(self, ):
        pass
    def savepoint(self, ):
        pass
    def transaction(self, ):
        pass

# 이걸로 가져가도 됨. 아니면 필요에 따라 DDL, DML 정도만 가져가던가.
# 함수 순서 정하기 및 입맛에 맞게 변경
class SQL(DDL, DML, DCL, TCL):
    def select(self, table=None, sql=None, many_execute=False, ):
        return super(SQL, self).select(table=table, sql=sql, many_execute=many_execute)
    def insert(self, sql=None, many_execute=False, file_path=None, data=None):
        super(SQL, self).insert(sql=sql, many_execute=many_execute, file_path=file_path, data=data)
    def delete(self, sql=None, many_execute=False, file_path=None, data=None):
        super(SQL, self).delete(sql=sql, many_execute=many_execute, file_path=file_path, data=data)
    def update(self,):
        super(SQL, self).update()