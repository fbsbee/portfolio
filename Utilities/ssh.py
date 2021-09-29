import paramiko

# ssh connect
hostname = '203.252.231.122'
username = 'cju'
password = 'cju'
ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy)
ssh.connect(hostname, username=username, password=password)
print('ssh connected')

# sftp connect
sftp = ssh.open_sftp()
localpath = ''
remotepath = ''
# file upload
sftp.put(localpath=localpath, remotepath=remotepath)

# file download
sftp.get(remotepath=remotepath, localpath=localpath)

ssh.close()