#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
import codecs
import os
from splinter import Browser

def output_class_exam(Score):
	
	file_object = open('/exam/'+exam, 'a', encoding = 'utf-8')
	
	file_object.write(Score[0]+' ')
	file_object.write(Score[1]+' ')
		
	for j in range(2,10):
		file_object.write(str(Score[j])+' ')
	
	file_object.write(str(Score[10])+'\n')
	
	file_object.close()

def get_score_from_html(num, str):

	st = str.index('姓名')+24
	ed = st+str[st::].find(' </span>')
	Name = str[st:ed:]
	
	st = str.index('语文')+58 if str.find('语文') != -1 else 0
	ed = st+str[st::].find('</div></td>')
	Chinese = float(str[st:ed:]) if st and st < ed else 0
	
	st = str.index('数学')+58 if str.find('数学') != -1 else 0
	ed = st+str[st::].find('</div></td>')
	Math = float(str[st:ed:]) if st and st < ed else 0
		
	st = str.index('英语')+58 if str.find('英语') != -1 else 0
	ed = st+str[st::].find('</div></td>')
	English = float(str[st:ed:]) if st and st < ed else 0
	
	st = str.index('物理')+58 if str.find('物理') != -1 else 0
	ed = st+str[st::].find('</div></td>')
	Physical = float(str[st:ed:]) if st and st < ed else 0
	
	st = str.index('化学')+58 if str.find('化学') != -1 else 0
	ed = st+str[st::].find('</div></td>')
	Chemistry = float(str[st:ed:]) if st and st < ed else 0
	
	st = str.index('生物')+58 if str.find('生物') != -1 else 0
	ed = st+str[st::].find('</div></td>')
	Biology = float(str[st:ed:]) if st and st < ed else 0
	
	Three = 0
	if min(Chinese, Math, English):
		Three = Chinese + Math + English
	
	SD = 0
	if min(Physical, Chemistry, Biology):
		SD = Physical + Chemistry + Biology
		
	All = 0
	if min(Three, SD):
		All = Three + SD
	
	Score = [num, Name, Chinese, Math, English, Physical, Chemistry, Biology, Three, SD, All]
	
	print (num, Name, Chinese, Math, English, Physical, Chemistry, Biology, Three, SD, All)
	
	output_class_exam(Score)

def catch(num):
	
	print ('Exam: '+exam+' Num: '+num+' '+time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())))
	
	browser.find_by_id('xuehao').fill(num+'\'or\'')
	browser.select('kaoshi', exam)
	time.sleep(0.5)
	browser.find_by_name('Submit').click()
	
	#file_object = open(exam+'-'+num, 'w', encoding = 'utf-8')
	#file_object.write(browser.html[2986:9006:])
	#file_object.close()
	
	if len(browser.html) > 2000:
	
		get_score_from_html(num, browser.html[2986:20000:])
		
	#else:
		
		#NoScore.append(num)
	
	browser.back()

def get_exam_score():

	print ('Start to Copy The Exam '+exam)
	
	for num in range(stars_num,32100):
	
		if num%100==99:
			
			browser.reload()
	
		if num%100>=1 and num%100<=70 and (num//100%100)>=1 and (num//100%100)<=20:
		
			catch(str(num))

if __name__ == '__main__':

	exam = input()
	
	stars_num = int(input())

	browser = Browser('chrome')
	browser.visit('http://jszx.stedu.net/jszxcj/search.htm')
	
	#List = ['10', '11', '120', '12', '13', '14', '15', '20', '21', '220', '22', '23', '24', '25', '30', '31', '32', '322', '330', '331', '33', '34', '35', '352', '36', '37']
	
	get_exam_score()
	
	browser.quit()
	