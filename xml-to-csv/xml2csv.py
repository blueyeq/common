#!/usr/bin/python
#XMLtoCSV.py
#_*_ encoding:utf-8 _*_
import csv, os
from xml.dom.minidom import parse

FILE_NAME="/Users/linyu/Documents/sy/API_NY/API_NY.GDP.MKTP.CD_DS2_zh_xml_v2"

def XML2CSV():
  csvFile = open(FILE_NAME+'.csv', 'wb')
  csvWriter = csv.writer(csvFile)
  xmlFile = open(FILE_NAME+'.xml')
  domTree = parse(xmlFile)
  #print domTree
  root = domTree.documentElement
#print dir(collection)
  num_record = 0
  bWriteHead = False
  for node in root.childNodes:
    if node.nodeType == node.ELEMENT_NODE:
    #print node.nodeName
      num_record+=1
      if num_record % 100 == 0:
        print('processed',num_record)
      element = {}
      bWriteHead = False
      print str(node.nodeName)
      keys=''
      values=''
      for leaf in node.childNodes:
        print leaf.hasAttributes()
      print(keys)
      return
      for key in node.attributes.keys():
        value = node.attributes.get(key).value
        element[key] = value
        print(tuple(element.values()))
        if len(element) > 0:
          if bWriteHead == False:
            csvWriter.writerow(tuple(element.keys()))
            bWriteHead = True
          csvWriter.writerow(tuple(element.values()))
        else:
          print(node.attributes)
  csvFile.close()
  xmlFile.close()
  print('processed ',num_record)

#def main():
#  for root, dirs, files in os.walk(os.getcwd()):
#    print root, dirs, files
#    for fname in files:
#    index = fname.find('.xml')
#    if index > 0:
#print index, fname[:index]
#    createCSVFile(fname[:index])
#  print "Transform " + fname + " OK!"

if __name__ == '__main__': 
  XML2CSV()  
  print('done.')
# sw=2;ts=2;sts=2;expandtab
