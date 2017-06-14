#!/bin/python

import json

json_file_input = "/Users/linyu/Documents/sy/geojson/highwayRailway.json"
json_file_output= "/Users/linyu/Documents/sy/geojson/highwayRailway_out.csv"

json_start1=",{"
json_start2="{"
json_end="}"


def convert_json(content):
  geo_json = json.loads(content)
  if geo_json['json_featuretype'] != 'highway':
    return '0'
  res=''
  for point in geo_json['json_geometry']['coordinates']:
    if len(res) > 0:
      res += ','
    str_point=str(point[0])+' '+ str(point[1])
    res += str_point
  print(res)
  return res

def process():
  print(json_file_input)
  file_in=open(json_file_input,"r")
  file_out=open(json_file_output,"w") 
  sum_line=0
  err_line=0
  json_content=""
  for line in file_in:
    line = line.strip()
    if line == json_start1 or line == json_start2:
      json_content="{"
    elif line == json_end:
      json_content += "}"
      try:
        rt=convert_json(json_content)
        sum_line += 1
        if rt != '0':
          print(rt)
          file_out.write(str(rt))
          file_out.write('\n')
      except:
        err_line += 1
    else:
      json_content += line
  
  print('sum_line:',sum_line)
  print('err_line:',err_line)
  file_in.close()
  file_out.close()

if __name__ == '__main__':
  process();

# sw=2;ts=2;sts=2;expandtab
