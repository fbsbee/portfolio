import smtplib
# from smtplib import SMTP
# prompt를 관리자 권한으로 실행, 이메일 계정 다른 어플에서 실행 가능하게 보안 허용 해주어야함. ( 구글은 들어가서 해야하는데...)
with smtplib.SMTP('smtp.gmail.com', 587) as smtp:
    # smtp = smtplib.SMTP('smtp.gmail.com', 587)
    smtp.ehlo()
    smtp.starttls() # TLS 사용시 필요
    smtp.login('aivautoscoringsystem@gmail.com', '#aass2021#')
    smtp.sendmail('aivautoscoringsystem@gmail.com', 'yyso1@naver.com', 'Subject: So long.\nDear Alice, so long and thanks for all the fish. Sincerely, Bob')
    # msg = MIMEText('it is smtp')
    # msg['Subject'] = '테스트'
    # msg['To'] = 'yyso1@naver.com'
    # smtp.sendmail('yourid@gmail.com', 'yourid@gmail.com', msg.as_string())