# 컴활 조회 코드
from selenium import webdriver
# from selenium.webdriver.common.by import By
# from selenium.webdriver.support.ui import WebDriverWait
# from selenium.webdriver.support import expected_conditions as EC
import winsound
import time

# 사용된 라이브러리 version
# msedge-selenium-tools==3.141.3
# selenium==3.141.0

# 컴퓨터 비프음 나는 코드
def speak_loud():
    frequency = 2500  # 주파수를 입력하세요
    duration = 1000  # 1000ms = 1sec
    winsound.Beep(frequency, duration)

# 실행 코드
def run(user_id, user_pw, user_sn_first, user_sn_last, site_url, driver_path, start=1, end=3, wait_time=3, first_page_time=2, intermission_time=1.5):
    if 'chrome' in driver_path :
        driver = webdriver.Chrome(driver_path)
    elif 'msedge' in driver_path:
        from msedge.selenium_tools import Edge, EdgeOptions
        options = EdgeOptions()
        options.use_chromium = True
        driver = Edge(executable_path=driver_path, options=options)
    else :
        # ie는 32bit용 driver 사용, 
        # 인터넷 옵션/보안 -> (인터넷, 로컬 인트라넷, 신뢰할 수 있는 사이트, 제한된 사이트) 4개 그림 다 보호 모드 사용 체크 해제
        driver = webdriver.Ie(driver_path)

    # 사이트 열기
    # driver.implicitly_wait(10)
    # button = WebDriverWait(driver, 10).until(EC.presence_of_element_located(By.CSS_SELECTOR, '#search_btn'))
    driver.get(site_url)

    # 로그인
    driver.find_element_by_name('uid').send_keys(user_id)
    driver.find_element_by_name('upwd').send_keys(user_pw)
    driver.find_element_by_class_name('btn_longin').click()

    # 2021/ 02/ 27 날짜로 ms chromium edge 사용시 alert 확인 필요.
    if 'msedge' in driver_path:
        time.sleep(intermission_time)
        driver.switch_to.alert.accept()

    # 홈 페이지 로딩 기다리는 시간
    time.sleep(first_page_time)

    # 홈 페이지
    # frame 전환을 해주어야 내부의 html tag를 읽을 수 있음
    driver.switch_to.frame(driver.find_element_by_xpath('//frame[@name="main"]'))
    # 개별접수 버튼 클릭
    driver.find_element_by_xpath('//*[@id="ulGNB"]/li[2]/a').click()
    # 시험접수 버튼 클릭
    driver.find_element_by_xpath('//*[@id="content_area"]/div/div/div[1]/ul/li[2]/a').click()
    time.sleep(intermission_time)
    
    # 1p
    # 컴활 실기 radio 클릭
    driver.find_element_by_xpath('//*[@id="exam_step1"]/input[4]').click()
    # 다음 버튼 클릭
    driver.find_element_by_xpath('//*[@id="content_area"]/div/div/div[2]/p/span/a').click()
    time.sleep(intermission_time)

    # 2p
    # 모두 동의 클릭
    driver.find_element_by_xpath('//*[@id="checkAll"]').click()
    # 약관 동의 버튼 클릭
    driver.find_element_by_xpath('//*[@id="content_area"]/div/div/div[2]/div[2]/div[2]/ul/p/span/a').click()
    time.sleep(intermission_time)

    # 3p
    # 컴활 등급 버튼 클릭
    driver.find_element_by_xpath('//*[@id="sc_elevel_1"]').click()
    # 프로그램(ms-office 2016) 버튼 클릭
    driver.find_element_by_xpath('//*[@id="sc_program_6"]').click()
    # 다음 버튼 클릭
    driver.find_element_by_xpath('//*[@id="myForm"]/div/div/div[2]/p/span/a').click()
    time.sleep(intermission_time)
    
    # 4p
    # 주민등록번호 앞, 뒤자리 입력 후 조회
    driver.find_element_by_name('sc_custno1').send_keys(user_sn_first)
    driver.find_element_by_name('sc_custno2').send_keys(user_sn_last)
    driver.find_element_by_xpath('//*[@id="btnCustno"]').click()
    # 알람 확인
    time.sleep(intermission_time)
    driver.switch_to.alert.accept()
    # 다음 버튼
    driver.find_element_by_xpath('//*[@id="myForm"]/p[2]/span/a').click()
    time.sleep(intermission_time)

    # 5p
    # 조회버튼
    check = driver.find_element_by_xpath('//span[@class="btn_blue_slong"]/a')
    # 조회버튼 클릭 수
    checking_num = 1

    # 조회하기
    while True:
        time.sleep(1) # 조회 클릭하기 위한 화면 로딩
        check.click()
        time.sleep(wait_time) # 텍스트 읽기 위한 화면 로딩

        # locations = 지역명, numbers = 갯수
        locations = (driver.find_elements_by_xpath(f'//*[@class="table_list0"]/tbody[2]/tr[{str(num)}]/td[2]')[0].text for num in range(start, start+end))
        numbers = (int(driver.find_elements_by_xpath(f'//*[@class="table_list0"]/tbody[2]/tr[{str(num)}]/td[5]')[0].text) for num in range(start, start+end))
        
        # 지역, 개수 출력 및 개수 1개 이상이면 비프음 나면서 프로그램 종료
        print(f'조회버튼 클릭 수 : {checking_num}')
        checking_num += 1
        for location, number in zip(locations, numbers):
            print(f'{location} : {number}')
            if number > 0 :
                speak_loud()
                input('수동으로 진행 중... 종료하려면 아무 키나 눌러주세요')
                return False
        print('=========================================')
    driver.close()
    driver.quit()
    
if __name__ == "__main__":

    # driver.exe 경로
    chromedriver_path = r'C:/chromedriver.exe'
    iedriver_path = r'C:/IEDriverServer.exe'
    edge_path = r'C:/msedgedriver.exe'

    # 순서대로 아이디, 비밀번호, 주민번호 앞자리, 주민번호 뒷자리 입력 해야 함
    # ex) user_id = 'abcd'
    # ex) user_pw = 'asdf1234'
    # ex) user_sn_first = 123456
    # ex) user_sn_last = 1234567

    user_id = '아이디'
    user_pw = '비밀번호'
    user_sn_first = 123456
    user_sn_last = 1234567
    
    # 사이트 경로
    site_url = "https://license.korcham.net/kor/member/login.jsp"

    # run(user_id=아이디, user_pw=패스워드, user_sn_first=주민번호 앞자리, user_sn_last=주민번호 뒷자리,
    #     site_url=크롤링 할 사이트 주소, driver_path=webdriver 경로, 
    #     start=신청할 주소의 목록 시작 위치, end=신청할 주소의 목록 개수,
    #     wait_time=기다리는 시간,
    #     first_page_time=홈 페이지 로딩 기다리는 시간(2초이상 추천),
    #     intermission_time=사이사이 페이지 로딩 기다리는 시간(1.5초 이상 추천))

    # start (신청할 주소의 목록 시작 위치) : 위에서 몇번째부터 시작할지 선택(default value : 1) (첫번째가 0이 아니라 1임)
    # end (신청할 주소의 목록 개수) : 목록 시작 위치부터 몇개 볼지 선택(default value : 3)
    # wait_time (기다리는 시간) (default value : 3)
    # first_page_time (default value : 2)
    # intermission_time (default value : 1.5)
    # 기다리는 시간 : 기본 1초에 사용자가 기다리는 시간을 추가로 넣어주면 됨 (default value : 3)
    # => 1 + 사용자가 추가한 시간 == 기다리는 시간

    run(user_id=user_id, user_pw=user_pw, user_sn_first=user_sn_first, user_sn_last=user_sn_last,
        site_url=site_url, driver_path=edge_path,
        end=4)