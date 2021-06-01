# stop_arduino
## 1. 블루투스 모듈 (HM-10) 사용 준비
```
AT+ROLE1
AT+IMME1
AT+RESET
```  
이거 입력 안하면 정보를 받아오지 않음  
  
## 2. 사용하는 커맨드
`AT+DISI?` : iBeacon 장치 가져오기  
OK+DISIS  
OK+DISC : `FactoryID` : `UUID` : `Major/Minor` : `MAC` : `RSSI`  
OK+DISCE
