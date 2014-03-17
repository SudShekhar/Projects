#!/usr/bin
import time
import os
import shutil
import re
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
#from selenium import JavascriptExecutor
from selenium.webdriver.common.proxy import *
from selenium.webdriver.common.by import By

#-------------------------|
#	Created by        |
#| Sudhanshu Shekhar      | 
#--------------------------
# No copyrights whatsoever.





"""starts Firefox webdriver instance with all the initial configurations"""
def beginFirefox(proxy):
	
	proxy = Proxy({
    'proxyType': ProxyType.MANUAL,
    'httpProxy': myProxy,
    'ftpProxy': myProxy,
    'sslProxy': myProxy,
    'noProxy': '' # set this value as desired
    })
	path = '/home/shekhar/testFolder/temp'
	handlers = ('application/octet-stream,' 'audio/wav,' 'audio/x-wav')
	profile = webdriver.FirefoxProfile()
	profile.set_preference("browser.download.folderList",2)
	profile.set_preference("browser.download.manager.showWhenStarting",False)
	profile.set_preference("browser.download.dir", path)
	profile.set_preference("browser.download.downloadDir", path)
	profile.set_preference("browser.download.defaultFolder", path)
	profile.set_preference("browser.helperApps.alwaysAsk.force", False)
	profile.set_preference("browser.helperApps.neverAsk.saveToDisk", handlers)
	profile.set_preference("pdfjs.disabled", True)
	#profile.update_preferences()

	driver = webdriver.Firefox(firefox_profile = profile,proxy=proxy)
	
	return driver

"""handes over control to this function on reaching the resources page. this returns the list of files to be downloaded"""
def downloadStuff(url,driver):
	table = driver.find_element(By.CSS_SELECTOR, ".Table > tbody:nth-child(1) > tr:nth-child(2) > td:nth-child(2) > font:nth-child(1) > table:nth-child(1) > tbody:nth-child(1)")
	links = table.find_elements_by_tag_name("a")
	files = []
	heading = driver.find_element(By.CSS_SELECTOR, ".Table > tbody:nth-child(1) > tr:nth-child(1) > td:nth-child(2) > font:nth-child(1) > center:nth-child(1) > u:nth-child(1)").text.encode('utf-8')
	path = '/home/shekhar/testFolder/temp/'
	os.mkdir(path+heading)
	heading+='/'
	
	numDownloaded = 0
	print " putting in files into " + heading
	for i in links:
		files.append(i.get_attribute("href").encode('utf-8'))
	for f in files:
			driver.get(f)
			numDownloaded +=1
			
	print str(numDownloaded) + " files downloaded "
	moveToFolder(path,files,heading)
	#print str(numDownloaded) + " is the number origianlly, we got  " + str(numMoved)
	#return files

"""gets the url download links , parses them to find file name and store them in appropriate directory"""
def moveToFolder(path,filesName,heading):
	numMoved = 0
	for f in filesName:
			fname = f.split('%')[-1][2:]
			wordList = fname.split('+')
			fname = reduce(lambda x,y: x+ ' ' + y, wordList)
			#print "moving " + fname + "to " + path+heading+fname
			try:
				shutil.move(path+fname,path+heading+fname)
				numMoved += 1 
			except IOError:
				print fname  + " couldn't be moved"
	print str(numMoved) + " files moved"
	time.sleep(2)
""" takes in webdriver instance and username and password ; returns the logged in webpage"""
def connectToisas(driver,username,password):
	driver.get("http://courses.iiit.ac.in")
	elem = driver.find_element_by_id("username")
	elem2 = driver.find_element_by_id("password")
	elem.send_keys(username)
	elem2.send_keys(password)
	driver.find_element_by_id("fm1").submit()
	return driver
	
def TimeToGo(driver):
		driver.close()
		exit(0)

def FindRegisteredCourses1(driver):
	table = driver.find_element(By.CSS_SELECTOR,".Table > tbody:nth-child(1) > tr:nth-child(1) > td:nth-child(2) > table:nth-child(1) > tbody:nth-child(1) > tr:nth-child(4) > td:nth-child(1) > table:nth-child(1)")		
	links = table.find_elements_by_tag_name("a")
	resourceLinks = []
	Rurl = "http://courses.iiit.ac.in/EdgeNet/resources.php?select="
	for i in links:
			courseUrl = i.get_attribute("href").encode('utf-8')
			temp = courseUrl.split('=')
			if len(temp) == 2:
				#	print "You have taken course " + temp[-1]
				resourceLinks.append(Rurl + temp[-1])
	return resourceLinks
			
myProxy = "http://proxy.iiit.ac.in:8080"
#driver = beginFirefox(myProxy)
USERNAME = "sudhanshu.shekhar@students.iiit.ac.in"
PASSWORD= "agnirocks"
#driver = connectToisas(driver,USERNAME,PASSWORD)
#now I have the main logged in page of isas ; need to find out all the registered course links

def main(myProxy,USERNAME,PASSWORD):
	driver = beginFirefox(myProxy)
	driver = connectToisas(driver,USERNAME,PASSWORD)
	#got list of resourcePages to crawl
	lst = FindRegisteredCourses1(driver)
	for i in lst:
		driver.get(i)
		downloadStuff(i,driver)
	TimeToGo(driver)
#driver.close();
#exit(0);
if __name__ == "__main__":
	myProxy = "http://proxy.iiit.ac.in:8080"
	USERNAME = "sudhanshu.shekhar@students.iiit.ac.in"
	PASSWORD = "agnirocks"
	main(myProxy,USERNAME,PASSWORD)
