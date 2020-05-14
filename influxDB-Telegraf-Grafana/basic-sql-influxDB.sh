#!/bin/bash

$ influx -username 'admin' -password 'admin'
#/create database test
#/use test
#/> insert temperature_and_humidity,building='skybiz',room='3609'   temperature=22.5,humidity=44.5
#/> insert memory,host=server01,region=korea value=5.5
#/> insert memory,host=server02,region=japan value=4.5
#/> select * from memory
#/> show measurements
#/> select "host", "time", "value" from memory where "host" = 'server01'
#/> insert memory,host=server03,name=alicek106 value=6.5
#/> select * from memory //그냥 추가됨. 없는 곳은 그냥 공백임.
#/> insert memory,host=server03,name=alicek106 value=6.5 //중복허용
#/> insert memory,host=server03,name=alicek106 value='abc' // value은 타입이 있다.
#/> insert memory,host=server03,name=alicek106 value=6.5 //tag는 타입이 없다.
> show field keys
name: memory
fieldKey fieldType
-------- ---------
value    float

name: temperature_and_humidity
fieldKey    fieldType
--------    ---------
humidity    float
temperature float

> show tag keys
name: memory
tagKey
------
host
name
region

name: temperature_and_humidity
tagKey
------
building
room

태그는 메타데이터, 필드는 실제 데이터

RestAPI 지원
$ curl -G 'http://localhost:8086/query?pretty=true' --data-urlencode "db=test" --data-urlencode "q=SELECT * FROM memory where host='server01'"
>> 
{
    "results": [
        {
            "statement_id": 0,
            "series": [
                {
                    "name": "memory",
                    "columns": [
                        "time",
                        "host",
                        "name",
                        "region",
                        "value"
                    ],
                    "values": [
                        [
                            "2018-03-10T11:47:21.044532805Z",
                            "server01",
                            null,
                            "korea",
                            5.5
                        ]
                    ]
                }
            ]
        }
    ]
}

url parameter도 지원한다.
[root@node01 ~] curl -i -XPOST 'http://localhost:8086/write?db=alicek106' --data-binary 'memory,host=server01,region=us-west value=0.65'

데이터를 무한히 저장하지 못하므로, 일정 주기마다 처리해 새롭게 저장하는 기능도 있다. 이것을 Down Sampling이라고 부른다.
CREATE CONTINUOUS QUERY "cq_30m" ON "food_data" BEGIN
  SELECT mean("website") AS "mean_website",mean("phone") AS "mean_phone"
  INTO "a_year"."downsampled_orders"
  FROM "orders"
  GROUP BY time(30m)
END

"food_data"는 DB이고,
"cq_30m"은 "Continuous Query(CQ)"이고
"orders"는 measurement이고
30m은 주기이고
"downsampled_orders"는 저장되는 measurement이고
mean("website")은 주기만큼 쌓인 것의 평균값을 "mean_website"에 저장
