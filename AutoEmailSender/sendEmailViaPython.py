#created by Sudhanshu Shekhar
# Took help from Captain DeadBones site for this piece of code
#it works really well.

#Extension Ideas:
# 1) Automate the process of sending out Happy Birthday mails. Create own script for the same
# 2) Can be used to create a spamming script

from time import sleep
import smtplib;
from email.mime.application import MIMEApplication
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

## account details
username = 'YOUR_EMAIL_ADDRESS'
password = 'YOUR_PASSWORD'
server = 'smtp.gmail.com:587'

def create_msg(to_address,from_address='',cc_address='',bcc_address='',subject=''):
	msg = MIMEMultipart();
	msg['Subject'] = subject;
	msg['To'] = to_address
	msg['Cc'] = cc_address
	msg['From'] = from_address;
	#msg['Subject'] = subject;
	return msg;

#send an email
def send_email(smtp_address,usr,password,msg,mode):
	server = smtplib.SMTP(smtp_address)
	server.ehlo();
	server.starttls()
	server.ehlo()
	server.login(username,password)
	if(mode == 0 and msg['To']!=''):
		server.sendmail(msg['From'],(msg['To'] +','+ msg['Cc']), msg.as_string())
	elif(mode == 1 and msg['Bcc']!=''):
		server.sendmail(msg['From'],(msg['To']+msg['Bcc']).split(","),msg.as_string())
	elif(mode!=1 and mode!=0):
		print 'error in sending mail bcc'
		print 'process cancelled'
		exit()
	server.quit()

#compose mail takes all detail for the mail and sends it in a specific format

def compose_mail(addresses,subject,body,files):
	to_add = addresses[0]
	cc_add = addresses[1]
	bcc_add = addresses[2]

	msg = create_msg(to_add,cc_address = cc_add,subject = subject)

	for text in body:
		attach_text(msg,text[0],text[1])
	
	if(files!=''):
		file_list = files.split(',')
		for afile in file_list:
			attach_file(msg,afile)
	
	send_email(server,username,password,msg,0)

	if(bcc_add!=''):
		msg['Bcc']  = bcc_add
		send_email(server,username,password,msg,1)
	print "email sent"

#attach text function
def attach_text(msg,atext,mode):
	part = MIMEText(atext,get_mode(mode))
	msg.attach(part)

def get_mode(mode):
	if mode == 0:
		return 'plain'
	elif mode == 1:
		return 'html'
	else: print ' error in text kind'; print 'email cancelled'; exit();

def attach_file(msg,afile):
	part = MIMEApplication(open(afile,"rb").read());
	part.add_header('Content-Disposition','attachment',filename= afile);
	msg.attach(part);

compose_mail(['abcd@gmail.com','',''],
		'checking out python script',
		[['some text will go here',0]],
		'File_To_Be_Attached');
