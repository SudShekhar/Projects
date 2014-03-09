from bs4 import BeautifulSoup
import urllib2
import os
import shutil

#|----------------------------------------|
#|   Created By Sudhanshu Shekhar         |
#|----------------------------------------|


url = "http://www.geeksforgeeks.org"
#Add more keywords here if needed. The script creates a folder for each tag and downloads all files related to the same
keywords = ["Dynamic Programming","Greedy Algorithms","Backtracking","Pattern Searching", "Divide & Conquer"
		, "Mathematical Algorithms", "Recursion","Geometric Algorithms"]

defaultPath = os.getcwd() + '/' + 'geeksforgeeks'
def createGeeksFolder(defaultPath):
	if os.path.isdir(defaultPath):
		for root,dirs,files in os.walk(defaultPath):
			for f in files:
				os.unlink(os.path.join(root,f))
			for d in dirs:
				shutil.rmtree(os.path.join(root,d))
			
		print "==== Created Folder geeksforgeeks in present working directory ==== "
	else : 
		os.mkdir(defaultPath)
		#created geeks for geeks folder
		print "==== Found Folder geeksforgeeks in present working directory ==== "

def getParsedPageData(url):
	htmlcontent = urllib2.urlopen(url).read()
	return BeautifulSoup(htmlcontent)

def getLinksFromTagNames(url,keywords,LinksToCrawl,hashLinkToKeyWord):
	#getting all the main page data
	MainPagecontent = getParsedPageData(url)
	for link in MainPagecontent.find_all('a'):
		if link.text in keywords:
			hashLinkToKeyWord[link['href']] = link.text
			LinksToCrawl.append(link['href'])

print "===================================Starting Download==============================================="

createGeeksFolder(defaultPath)
hashLinkToKeyWord = {}
LinksToCrawl=[]
getLinksFromTagNames(url,keywords,LinksToCrawl,hashLinkToKeyWord)
#got the link corresponding to each tag

#now we loop through all the tagged pages
for link in LinksToCrawl:
	IndexPageLinks = []
	newPath = defaultPath + '/' + hashLinkToKeyWord[link]
	os.mkdir(newPath)
	print " \n\n***** Created Folder ==> "+ hashLinkToKeyWord[link] + " *****"
	#created a folder with the Tag Name inside the geeksforgeeks folder 
	link+='/'
	IndexPageLinks.append(link)
	LinkPageContent = getParsedPageData(link)
	for l in LinkPageContent.find_all('a'):
		if l.has_attr('class'):
			if l['class'] == ['page', 'larger']:
				tempUrl = l['href']
				IndexPageLinks.append(tempUrl)
	#we extract all number of tagged pages (with one keyword and then add that to the present path)			
	#now going to all the /number pages and getting their content
	num = 0
	for i in IndexPageLinks:
		lpcontent = urllib2.urlopen(i).read()
		ParsedContent = BeautifulSoup(lpcontent)
		for i in ParsedContent.find_all(rel = 'bookmark'):
			num+=1
			filename = reduce(lambda x,y : x+y,i.text.split('/'))
			flname = newPath + '/' + filename+'.htm'
			print " => Downloading " + filename
			fl = open(flname,"w")
			data = urllib2.urlopen(i['href']).read()
			fl.write(data)
			fl.close()
print " ========= Download Finished =========="


