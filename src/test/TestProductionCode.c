
#include "TestProductionCode.h"
#include "unity.h"
#include "unity_internals.h"
#include "testMockCommands.h"
#include "string.h"   /*memset*/
#include "certificates.h"

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

char inputBuffer[1024];
cmData_t cmData = CM_DATA_INITIALIZER ;

char *MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;

void setUp(void)
{
  /* This is run before EACH TEST */
}

void tearDown(void)
{    
    //TEST_IGNORE_MESSAGE("ignorado");
}


void test_modem_initializer(){
    cmError_t retValue = CM_FAIL;
    /*lauch fail -1 because not initialize correctly*/
    retValue = cellModem_Init(&cmData,inputBuffer,CM_BUFFER_LEN_DEF,NULL,OutputFunction,NULL);
    TEST_ASSERT_EQUAL_INT32(CM_FAIL,retValue);

    retValue = cellModem_Init(NULL,inputBuffer,CM_BUFFER_LEN_DEF,NULL,OutputFunction,NULL);
    TEST_ASSERT_EQUAL_INT32(CM_FAIL,retValue);

    retValue = cellModem_Init(&cmData,inputBuffer,CM_BUFFER_LEN_DEF,GetTickCountMs,OutputFunction,NULL);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetNetworkInformation(){
    cmError_t retValue = CM_FAIL;
    netInfo_t getnetInfo = NETINFO_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_QNWINFO_RESPONSE;
    retValue = cellModem_GetNetworkInformation(&cmData, &getnetInfo);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    TEST_ASSERT_EQUAL_STRING("FDD LTE",getnetInfo.accessTechnSel);
    TEST_ASSERT_EQUAL_STRING("732101",getnetInfo.operator);
    TEST_ASSERT_EQUAL_STRING("LTE BAND 7",getnetInfo.band);
    TEST_ASSERT_EQUAL_STRING("3075",getnetInfo.channelId);

    memset(&getnetInfo,0,sizeof(getnetInfo));
    MockResponseExpected = CM_CMD_MOCK_QNWINFO_RESPONSE2_ECHO;
    retValue = cellModem_GetNetworkInformation(&cmData, &getnetInfo);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    TEST_ASSERT_EQUAL_STRING("EDGE",getnetInfo.accessTechnSel);
    TEST_ASSERT_EQUAL_STRING("732101",getnetInfo.operator);
    TEST_ASSERT_EQUAL_STRING("GSM 1900",getnetInfo.band);
    TEST_ASSERT_EQUAL_STRING("583",getnetInfo.channelId);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetModuleInformation(){
    cmError_t retValue = CM_FAIL;
    modemInfo_t getModemInfo = MODEMINFO_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_ATI_RESPONSE2_ECHO;//CM_CMD_MOCK_ATI_RESPONSE;
    retValue = cellModem_GetModuleInformation(&cmData, &getModemInfo);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    TEST_ASSERT_EQUAL_STRING("Quectel",getModemInfo.manufactorId);
    TEST_ASSERT_EQUAL_STRING("BG96",getModemInfo.deviceModel);
    TEST_ASSERT_EQUAL_STRING("Revision: BG96MAR02A07M1G",getModemInfo.firmwareVersion);

    MockResponseExpected = CM_CMD_MOCK_ATI_RESPONSE;
    retValue = cellModem_GetModuleInformation(&cmData, &getModemInfo);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    TEST_ASSERT_EQUAL_STRING("Quectel",getModemInfo.manufactorId);
    TEST_ASSERT_EQUAL_STRING("EC25",getModemInfo.deviceModel);
    TEST_ASSERT_EQUAL_STRING("Revision: EC25AUXGAR08A03M1G",getModemInfo.firmwareVersion);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetImei(){
    cmError_t retValue = CM_FAIL;
    char getImei[32]="\0";

    MockResponseExpected = CM_CMD_MOCK_GSN_RESPONSE;

    retValue = cellModem_GetImei(&cmData, getImei);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_STRING("862708040783073",getImei);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetImsi(){
    cmError_t retValue = CM_FAIL;
    char getImsi[32]="\0";

    MockResponseExpected = CM_CMD_MOCK_IMSI_RESPONSE;

    retValue = cellModem_GetImsi(&cmData, getImsi);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_STRING("732101596840439",getImsi);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetIccid(){
    cmError_t retValue = CM_FAIL;
    char getIccid[32]="\0";

    MockResponseExpected = CM_CMD_MOCK_CCID_RESPONSE;

    retValue = cellModem_GetIccid(&cmData, getIccid);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_STRING("89571015025068994296",getIccid);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetSignalQuality(){
    cmError_t retValue = CM_FAIL;
    uint8_t rssi = 0;

    MockResponseExpected = CM_CMD_MOCK_GSQ_RESPONSE;
    retValue = cellModem_GetSignalQuality(&cmData, &rssi);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_UINT8(28,rssi);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SetATE(){
    cmError_t retValue = CM_FAIL;

    MockResponseExpected = CM_CMD_MOCK_ATE1_RESPONSE;
    retValue = cellModem_SetATE(&cmData,1);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    MockResponseExpected = CM_CMD_MOCK_ATE0_RESPONSE;
    retValue = cellModem_SetATE(&cmData,0);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SetATV(){
    cmError_t retValue = CM_FAIL;

    MockResponseExpected = CM_CMD_MOCK_ATV1_RESPONSE;
    retValue = cellModem_SetATV(&cmData,1);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    /*se cambia respuesta de la Irs por que se cambio el formato de respuesta a  ATV0*/
    //MockResponseExpected = CM_CMD_MOCK_ATV0_RESPONSE;
    //retValue = cellModem_SetATV(&cmData,0);
    //TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    /*vuelve init a respuesta ATV1 o enviar literal ATV1*/
    MockResponseExpected = CM_CMD_MOCK_ATV1_RESPONSE;
    retValue = cellModem_SetATV(&cmData,1);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  

  
}

void test_modem_GetCREG(){
    cmError_t retValue = CM_FAIL;
    netRegStatus_t netRegSta=NETREGSTATUS_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_CREG_RESPONSE;
    retValue = cellModem_GetCREG(&cmData,&netRegSta);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    TEST_ASSERT_EQUAL_INT(0,netRegSta.n);
    TEST_ASSERT_EQUAL_INT(1,netRegSta.stat);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetCOPS(){
    cmError_t retValue = CM_FAIL;
    netOperatorStatus_t netOperatorStat = NETOPERATORSTATUS_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_COPS_RESPONSE;
    retValue = cellModem_GetCOPS(&cmData,&netOperatorStat);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    TEST_ASSERT_EQUAL_INT(0,netOperatorStat.mode);
    TEST_ASSERT_EQUAL_INT(0,netOperatorStat.format);
    TEST_ASSERT_EQUAL_STRING("#CoberturaCLARO Claro",netOperatorStat.operator);
    TEST_ASSERT_EQUAL_INT(7,netOperatorStat.act);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetCPIN(){
    cmError_t retValue = CM_FAIL;
    char getCode[32]={0};

    MockResponseExpected = CM_CMD_MOCK_CPIN_RESPONSE;
    retValue = cellModem_GetCPIN(&cmData,getCode);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_STRING("READY",getCode);

    memset(getCode,0,sizeof(getCode));
    MockResponseExpected = CM_CMD_MOCK_CPIN_RESPONSE_BAD;
    retValue = cellModem_GetCPIN(&cmData,getCode);
    TEST_ASSERT_EQUAL_INT32(CM_ERR_INVALID_RESPONSE,retValue);
    //TEST_ASSERT_EQUAL_STRING("READY",getCode);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  

}

void test_modem_SetApn(){
    //TEST_IGNORE_MESSAGE("This Test Was Ignored, This Function Has Not Been Tested, Needs To Be Implemented");
    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config =CELLMODEMCONFIG_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    config.apn ="INTERNET.COMCEL.COM.CO";
    config.apnPassw = "CLARO";
    config.apnUser ="COMCEL";
    retValue = cellModem_SetApn(&cmData,&config);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SetContextProfile(){
    //TEST_IGNORE_MESSAGE("This Test Was Ignored, This Function Has Not Been Tested, Needs To Be Implemented");
    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config =CELLMODEMCONFIG_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    config.contextId = 1;
    retValue = cellModem_SetContextProfile(&cmData,&config);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_GetContextProfile(){
    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config = CELLMODEMCONFIG_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_QIACT_GET_RESPONSE;
    retValue = cellModem_GetContextProfile(&cmData,&config);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
 
    TEST_ASSERT_EQUAL_INT32(1, config.contextId);
    TEST_ASSERT_EQUAL_INT32(1, config.contextState);
    TEST_ASSERT_EQUAL_INT32(1, config.contextType);
    TEST_ASSERT_EQUAL_STRING("10.101.234.65",config.contextIpAddres);

/*respuesta mala,no se usan datos*/
    memset(&config, 0 ,sizeof(config));
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_GetContextProfile(&cmData,&config);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SetDeactContextProfile(){
    cmError_t retValue = CM_FAIL;
  
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SetDeactContextProfile(&cmData, 1);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    MockResponseExpected = CM_CMD_MOCK_ERROR_GENERAL_RESPONSE;
    retValue = cellModem_SetDeactContextProfile(&cmData, 1);
    TEST_ASSERT_EQUAL_INT32(CM_ERR_INVALID_RESPONSE,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SmsSetMessageFormat(){
    cmError_t retValue = CM_FAIL;
    
    /*DPU format*/
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SmsSetMessageFormat(&cmData, 0);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    /*text format*/
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SmsSetMessageFormat(&cmData,1);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SmsSetTextModeParam(){
    cmError_t retValue = CM_FAIL;
    
    /*text format*/
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SmsSetTextModeParam(&cmData);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SmsSetTeCharacterGsm(){
    cmError_t retValue = CM_FAIL;
    
    /*GSM default alphabet */
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SmsSetTeCharacterGsm(&cmData);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SmsSendNumber(){
    cmError_t retValue = CM_FAIL;
    
    /*GSM default alphabet */
    MockResponseExpected = ">";//CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SmsSendNumber(&cmData,"3146644565");
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}

void test_modem_SmsSendTextMessage(){
    cmError_t retValue = CM_FAIL;
    
    /*GSM default alphabet */
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SmsSendTextMessage(&cmData,"Hellow world!");
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
}


void test_modem_SocketOpen(){
    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config =CELLMODEMCONFIG_INITIALIZER;
    socketData_t configSocket =SOCKETDATA_INITIALIZER;
    MockResponseExpected = CM_CMD_MOCK_QIOPEN_RESPONSE;
    configSocket.accessMode = 0;
    configSocket.contextId = config.contextId = 1;
    configSocket.connectId = config.connectId = 3;
    configSocket.serviceType = CELLMODEM_SOCKET_SRV_TYPE_UDP;
    strcpy(configSocket.remip , "127.0.0.1");
    strcpy(configSocket.remPort , "0");
    strcpy(configSocket.locPort , "2020" );
    retValue = cellModem_SocketOpen(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
    
}

void test_modem_SocketGetServStatus(){
    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config =CELLMODEMCONFIG_INITIALIZER;
    socketData_t configSocket =SOCKETDATA_INITIALIZER;


    MockResponseExpected = CM_CMD_MOCK_QISTATE_RESPONSE;

    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(3, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("10.106.6.155",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("0",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("5500",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(3,configSocket.state);

    configSocket.connectId = config.connectId = 11;
    MockResponseExpected = CM_CMD_MOCK_QISTATE_RESPONSE_INCOMING_CLIENT;
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("192.168.32.68",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("54842",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("5500",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(2,configSocket.state);
    
    configSocket.connectId = config.connectId = 11;
    MockResponseExpected = CM_CMD_MOCK_QISTATE_RESPONSE2_ECHO;
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(3, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("10.101.234.65",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("0",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("2020",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(4,configSocket.state);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  

    memset(configSocket.locPort,0,8);
    configSocket.connectId = config.connectId = 3;
    MockResponseExpected = CM_CMD_MOCK_QISTATE_SERIAL_RESPONSE;
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(3, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("6000",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("0",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(1,configSocket.state);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));   

        configSocket.connectId = config.connectId = 11;
    MockResponseExpected = "AT+QISTATE=1,11\r\r\nOK\r\n";
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("\0",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("\0",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(0,configSocket.state);
    TEST_ASSERT_EQUAL_INT(0,configSocket.serverId);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  

    configSocket.connectId = config.connectId = 11;
    MockResponseExpected = "AT+QISTATE=1,11\r\r\n+QISTATE: 11,\"TCP INCOMING\",\"192.168.32.48\",54707,2020,4,1,3,0,\"uart1\"\r\n\r\nOK\r\n";
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("54707",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("2020",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(4,configSocket.state);
    TEST_ASSERT_EQUAL_INT(3,configSocket.serverId);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));

        configSocket.connectId = config.connectId = 11;
    MockResponseExpected = "AT+QISTATE=1,11\r\r\n+QISTATE: 11,\"TCP INCOMING\",\"192.168.32.48\",54707,2020,4,1,5,0,\"uart1\"\r\n\r\nOK\r\n";
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("54707",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("2020",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(4,configSocket.state);
    TEST_ASSERT_EQUAL_INT(5,configSocket.serverId);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));

    
           configSocket.connectId = config.connectId = 11;
    MockResponseExpected =CM_CMD_MOCK_QIURC_RECV_WITH_QISTATE_RESPONSE;
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("55647",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("2020",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(2,configSocket.state);
    TEST_ASSERT_EQUAL_INT(3,configSocket.serverId);
    TEST_ASSERT_EQUAL_INT(1, cmIsAsyncEvent(&cmData));
    cmClearAllAsyncEvent(&cmData);

    configSocket.connectId = config.connectId = 2;
    MockResponseExpected =CM_CMD_MOCK_QISTATE_SERV_WITH_QISTATE_CONFIG_RESPONSE; 
    retValue = cellModem_SocketGetServStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(2, configSocket.connectId);
    TEST_ASSERT_EQUAL_STRING("10.101.234.65",configSocket.ipAddres);
    TEST_ASSERT_EQUAL_STRING("0",configSocket.remPort);
    TEST_ASSERT_EQUAL_STRING("9999",configSocket.locPort);
    TEST_ASSERT_EQUAL_INT(3,configSocket.state);
    TEST_ASSERT_EQUAL_INT(2,configSocket.serverId);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));

}


void test_modem_SocketGetRecv(){
    char bufferRecv[CM_BUFFER_LEN_DEF] ;


    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config =CELLMODEMCONFIG_INITIALIZER;
    socketData_t configSocket =SOCKETDATA_INITIALIZER;
    configSocket.msgRecv = bufferRecv;
    configSocket.buffRcvLen = CM_BUFFER_LEN_DEF;
   MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE;

    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(6, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("julian",configSocket.msgRecv);

  
   // memset(bufferRecv,0,sizeof(bufferRecv));
    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_LONG;

    configSocket.connectId = config.connectId = 11;
    
    retValue = cellModem_SocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(112, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA036610330A166E6E7006128A109060760857405080102A203020101A305A10302010DBE0F040D0800065F04001802201388FA0074EA7E",configSocket.msgRecv);

    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_EMPTY_BUFF;

    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(0, configSocket.msgLen);
    //TEST_ASSERT_EQUAL_STRING(" ",configSocket.msgRecv);

    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_ECHO;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(6, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("julian",configSocket.msgRecv);

    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_STR;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(246, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("Buenas a todos! Estaba chusmeando el proyecto. Los navigation devices esten teniendo un conjunto de posiciones, que se espera hacer con eso? Ponemos todas las posiciones en el mapa, hacemos un calculo en el front, que representan esas posiciones?",configSocket.msgRecv);

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    configSocket.recvHexString = 1;
    retValue = cellModem_SocketDataFormat(&cmData,configSocket.recvHexString);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);

    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_HEX_STR;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData, &configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    TEST_ASSERT_EQUAL_INT32(18, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA02100020023037E", configSocket.msgRecv);

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    configSocket.recvHexString = 1;
    retValue = cellModem_SocketDataFormat(&cmData,configSocket.recvHexString);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);

    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_HEX_STR_LARGE;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData, &configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    TEST_ASSERT_EQUAL_INT32(70, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA0210002002303939A7481801205018006018007040000000108040000000341187E", configSocket.msgRecv);
    
    unsigned char buffHex[512] ={0};
    unsigned char buffExpected[512]={0x7E, 0xA0,0x21 ,0x00 ,0x02 ,0x00 ,0x23 ,0x03 ,0x93 ,0x9A ,0x74 ,0x81 ,0x80 ,0x12 ,0x05 ,0x01 ,0x80 ,0x06 ,0x01 ,0x80 ,0x07 ,0x04 ,0x00 ,0x00 ,0x00 ,0x01 ,0x08 ,0x04 ,0x00 ,0x00 ,0x00 ,0x03 ,0x41 ,0x18 ,0x7E};
    int val = cellModem_StrToHexBuffer(configSocket.msgRecv,buffHex, (int)configSocket.msgLen);
    TEST_ASSERT_GREATER_THAN_INT16(0,val);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(buffExpected,buffHex,configSocket.msgLen);

    //disable recv hexstr
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    configSocket.recvHexString = 0;
    retValue = cellModem_SocketDataFormat(&cmData,configSocket.recvHexString);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    
    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_LONG;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData, &configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    TEST_ASSERT_EQUAL_INT32(112, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA036610330A166E6E7006128A109060760857405080102A203020101A305A10302010DBE0F040D0800065F04001802201388FA0074EA7E", configSocket.msgRecv);

   }


void test_modem_QIURC_incoming(){
    cmError_t retValue;
    MockResponseExpected = CM_CMD_MOCK_QIURC_CONN_INCOMING_RESPONSE;

    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_CONN_INCOMING_RESPONSE,cmGetBufferRecv(&cmData));


    MockResponseExpected = CM_CMD_MOCK_QIURC_CONN_FULL_RESPONSE;
    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_CONN_FULL_RESPONSE,cmGetBufferRecv(&cmData));

    
    MockResponseExpected = CM_CMD_MOCK_QIURC_CONN_CLOSED_RESPONSE;

    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_CONN_CLOSED_RESPONSE,cmGetBufferRecv(&cmData));

    
    MockResponseExpected = CM_CMD_MOCK_QIURC_RECV_RESPONSE;

    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_RECV_RESPONSE,cmGetBufferRecv(&cmData));
    (void)retValue;

}
/*The data must be previously loaded
   // mempcy( cmData.rxData.bufferAsyncEvent , ": \"incoming\",7,3,\"192.168.32.68\",41047\r\n",47);
   // cmData.rxData.asyncEvent = 1;
   */
void test_modem_QIURC_incomingConnection(){
    cmError_t retValue = CM_FAIL; 
    asynEventIncomingConn_t getDataIncomingConn = ASYNCEVENT_INCOMING_CONN_INITIALIZER;

    MockResponseExpected = CM_CMD_MOCK_QIURC_CONN_INCOMING_RESPONSE;
    cmClearAllAsyncEvent(&cmData);
    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_CONN_INCOMING_RESPONSE,cmGetBufferRecv(&cmData));
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    retValue = cellModem_UrcGetDataIncomingConnection(&cmData, &getDataIncomingConn);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, getDataIncomingConn.info.connectId);
    TEST_ASSERT_EQUAL_INT32(1, getDataIncomingConn.serverId);
    TEST_ASSERT_EQUAL_INT32(63713, getDataIncomingConn.remotePort);
    TEST_ASSERT_EQUAL_STRING("192.168.32.68", getDataIncomingConn.remoteIp);

    
        MockResponseExpected = CM_CMD_MOCK_QIURC_CONN_INCOMING_PDPDEACT_RESPONSE;
    cmClearAllAsyncEvent(&cmData);
    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_CONN_INCOMING_PDPDEACT_RESPONSE,cmGetBufferRecv(&cmData));
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    retValue = cellModem_UrcGetDataIncomingConnection(&cmData, &getDataIncomingConn);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, getDataIncomingConn.info.connectId);
    TEST_ASSERT_EQUAL_INT32(3, getDataIncomingConn.serverId);
    TEST_ASSERT_EQUAL_INT32(63713, getDataIncomingConn.remotePort);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48", getDataIncomingConn.remoteIp);
}

void test_modem_QIURC_closedConnection(){
    cmError_t retValue = CM_FAIL; 
    asynEventURC_t getDataClosedConn ;

    MockResponseExpected = CM_CMD_MOCK_QIURC_CONN_CLOSED_RESPONSE;
    cmClearAllAsyncEvent(&cmData);
    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_CONN_CLOSED_RESPONSE,cmGetBufferRecv(&cmData));

    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    retValue = cellModem_UrcGetClosedConnection(&cmData, &getDataClosedConn);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(10, getDataClosedConn.connectId);
}

void test_modem_QIURC_RecvConnection(){
    cmError_t retValue = CM_FAIL; 
    asynEventURC_t getRecvConn ;

    MockResponseExpected = CM_CMD_MOCK_QIURC_RECV_RESPONSE;
    cmClearAllAsyncEvent(&cmData);
    retValue = cellModem_SendRaw(&cmData, "AT\r");   // solo para que funcione el test debe enviar algo
   // TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_RECV_RESPONSE,cmGetBufferAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_QIURC_RECV_RESPONSE,cmGetBufferRecv(&cmData));

    (void)retValue;

    TEST_ASSERT_EQUAL_INT32(1 ,cmIsAsyncEvent(&cmData));
    retValue = cellModem_UrcGetRecvConnection(&cmData, &getRecvConn);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(10, getRecvConn.connectId);
}

void test_modem_SocketClose(){
    cmError_t retValue = CM_FAIL;
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SocketClose(&cmData,10);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SocketSendData(){
    cmError_t retValue = CM_FAIL;
    socketData_t socketData = SOCKETDATA_INITIALIZER;
    char data[1024] = "hola lalala";
    MockResponseExpected = ">";//CM_CMD_MOCK_GENERAL_RESPONSE;
    socketData.connectId = 1;
    //socketData.serviceType = cellModem_SOCKET_SRV_TYPE_TCP;
    socketData.dataToSend = data;
    retValue = cellModem_SocketConfigSendData(&cmData,&socketData);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    retValue = CM_FAIL;
    MockResponseExpected = CM_CMD_MOCK_QISEND_OK_RESPONSE;
    retValue = cellModem_SocketSendData(&cmData,&socketData);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SocketSendDataHex(){
    cmError_t retValue = CM_FAIL;
    static socketData_t socketData = SOCKETDATA_INITIALIZER;
    cellModemConfig_t config = CELLMODEMCONFIG_INITIALIZER;
   static  char data_dest[1024]={0};
   	static char *dataSend = NULL;
   // unsigned char buffExpected[512]={0x7E, 0xA0,0x21 ,0x00 ,0x02 ,0x00 ,0x23 ,0x03 ,0x93 ,0x9A ,0x74 ,0x81 ,0x80 ,0x12 ,0x05 ,0x01 ,0x80 ,0x06 ,0x01 ,0x80 ,0x07 ,0x04 ,0x00 ,0x00 ,0x00 ,0x01 ,0x08 ,0x04 ,0x00 ,0x00 ,0x00 ,0x03 ,0x41 ,0x18 ,0x7E};

unsigned char buffExpected[1024]={0x7E, 0xA8, 0x8C, 0x03, 0x00, 0x02, 0x00, 0x23, 0x20, 0x08, 0xF9, 0xE6, 0xE7, 0x00, 0xC4, 0x02, 0x81, 0x00, 0x00, 0x00, 
0x00, 0x01, 0x00, 0x82, 0x03, 0x31, 0x01, 0x82, 0x02, 0x35, 0x02, 0x07, 0x02, 0x02, 0x09, 0x0C, 0x07, 0xE5, 0x0B, 0x03, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0xFF, 0x04, 0x06, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 
0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 
0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 
0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 
0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x30, 
0xA1, 0x7E, 0x7E, 0xA8, 0x8C, 0x03, 0x00, 0x02, 0x00, 0x23, 0x22, 0x1A, 0xDA, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 
0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 
0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
0x00, 0xAE, 0xFB, 0x7E, 0x7E, 0xA8, 0x8C, 0x03, 0x00, 0x02, 0x00, 0x23, 0x34, 0xAD, 0xAF, 0x10, 0x00, 0x00, 0x10, 0x27, 
0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 
0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 
0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 
0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
0x10, 0x00, 0x00, 0x10, 0x27, 0x10, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x27, 
0x10, 0x02, 0x07, 0xE0, 0x71, 0x7E};

    socketData.connectId = 1;
    //dataSend = buffExpected;
    cellModem_HexToStrBuffer(buffExpected,data_dest, 426);//35 426
    socketData.dataToSend = data_dest ;
   // TEST_ASSERT_EQUAL_STRING("7EA0210002002303939A7481801205018006018007040000000108040000000341187E",socketData.dataToSend);

    MockResponseExpected = CM_CMD_MOCK_QISEND_OK_RESPONSE;
    retValue = cellModem_SocketSendDataHex(&cmData,&socketData);
   // TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    MockResponseExpected = CM_CMD_MOCK_QIACT_GET_RESPONSE;
    retValue = cellModem_GetContextProfile(&cmData,&config);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
 
    TEST_ASSERT_EQUAL_INT32(1, config.contextId);
    TEST_ASSERT_EQUAL_INT32(1, config.contextState);
    TEST_ASSERT_EQUAL_INT32(1, config.contextType);
    TEST_ASSERT_EQUAL_STRING("10.101.234.65",config.contextIpAddres);
}

void test_modem_SSLCfgPathCacert(){
    cmError_t retValue = CM_FAIL;
    SSLcfgCAcert_t SSLcfgCAcert = INITIALIZER_SSLCFG_CACERT;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    SSLcfgCAcert.sslctxID = 1;
    SSLcfgCAcert.cacertPath = "cacert.pem";


    retValue = cellModem_SSLCfgPathCacert(&cmData,&SSLcfgCAcert);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLCfgPathClientCert(){
    cmError_t retValue = CM_FAIL;
    SSLcfgClientCert_t SSLcfgClientCert = INITIALIZER_SSLCFG_CLIENTCERT;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    SSLcfgClientCert.sslctxID = 1;
    SSLcfgClientCert.clientCertPath = "user_cert.pem";


    retValue = cellModem_SSLCfgPathClientCert(&cmData,&SSLcfgClientCert);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLCfgPathClientKeyCert(){
    cmError_t retValue = CM_FAIL;
    SSLcfgKeyCert_t SSLcfgKeyCert = INITIALIZER_SSLCFG_KEYCERT;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    SSLcfgKeyCert.sslctxID = 1;
    SSLcfgKeyCert.clientKeyPath = "user_key.pem";


    retValue = cellModem_SSLCfgPathClientKeyCert(&cmData,&SSLcfgKeyCert);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLCfgSecLevel(){
    cmError_t retValue = CM_FAIL;
    SSLcfgSecLevel_t SSLcfgSecLevel = INITIALIZER_SSLCFG_SECLEVEL;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    SSLcfgSecLevel.sslctxID = 1;
    SSLcfgSecLevel.secLevel = 2;

    retValue = cellModem_SSLCfgSecLevel(&cmData,&SSLcfgSecLevel);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLCfgVersion(){
    cmError_t retValue = CM_FAIL;
    SSLcfgVersion_t SSLcfgVersion = INITIALIZER_SSLCFG_VERSION;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    SSLcfgVersion.sslctxID = 1;
    SSLcfgVersion.sslVersion = 4;

    retValue = cellModem_SSLCfgVersion(&cmData,&SSLcfgVersion);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLCfgCipherSuite(){
    cmError_t retValue = CM_FAIL;
    SSLcfgCipherSuite_t SSLcfgCipherSuite = INITIALIZER_SSLCFG_CIPHERSUITE;

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    SSLcfgCipherSuite.sslctxID = 1;
    SSLcfgCipherSuite.cipherSuite = TSL_SUPPORT_ALL;

    retValue = cellModem_SSLCfgCipherSuite(&cmData,&SSLcfgCipherSuite);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    SSLcfgCipherSuite.cipherSuite = TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384;

    retValue = cellModem_SSLCfgCipherSuite(&cmData,&SSLcfgCipherSuite);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLDeleteFileStorage(){
    cmError_t retValue = CM_FAIL;
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SSLDeleteFileStorage(&cmData,"UFS:*");
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLListFileStorage(){
    cmError_t retValue = CM_FAIL;
    MockResponseExpected = CM_CMD_MOCK_SSL_LISTFILE;
    char output[512] = {0};

    retValue = cellModem_SSLListFileStorage(&cmData,"UFS:*",output );
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_STRING(CM_CMD_MOCK_SSL_LISTFILE,output);
}


void test_modem_SSLUplCaCert(){
    cmError_t retValue = CM_FAIL;
    MockResponseExpected = "CONNECT\r";

    retValue = cellModem_SSLUplCert(&cmData, "UFS:cacert.pem", strlen(CA_CERT) );
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    MockResponseExpected = CM_CMD_MOCK_SSL_UPLFILE;
    retValue = cellModem_SSLSendFile(&cmData, CA_CERT "\r" );
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLUplClientCert(){
    cmError_t retValue = CM_FAIL;
    MockResponseExpected = "CONNECT\r";

    retValue = cellModem_SSLUplCert(&cmData, "UFS:user_cert.pem", strlen(USER_CLIENT_CERT) );
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    MockResponseExpected = CM_CMD_MOCK_SSL_UPLFILE;
    retValue = cellModem_SSLSendFile(&cmData, USER_CLIENT_CERT "\r" );
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLUplKeyCert(){
    cmError_t retValue = CM_FAIL;
    MockResponseExpected = "CONNECT\r";

    retValue = cellModem_SSLUplCert(&cmData, "UFS:user_key.pem", strlen(USER_KEY_CERT) );
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    MockResponseExpected = CM_CMD_MOCK_SSL_UPLFILE;
    retValue = cellModem_SSLSendFile(&cmData, USER_KEY_CERT "\r" );
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}


void test_modem_SSLSocketSendData(){
    cmError_t retValue = CM_FAIL;
    SSLSocketData_t socketData = INITIALIZER_SSL_SOCKET_DATA;
    char data[1024] = "hola lalala";
    MockResponseExpected = ">";//CM_CMD_MOCK_GENERAL_RESPONSE;
    socketData.clientID = 1;
    //socketData.serviceType = cellModem_SOCKET_SRV_TYPE_TCP;
    socketData.dataToSend = data;
    retValue = cellModem_SSLSocketConfigSendData(&cmData,&socketData);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);

    retValue = CM_FAIL;
    MockResponseExpected = CM_CMD_MOCK_QISEND_OK_RESPONSE;
    retValue = cellModem_SSLSocketSendData(&cmData,&socketData);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}

void test_modem_SSLSocketGetStatus(){
    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config =CELLMODEMCONFIG_INITIALIZER;
    SSLSocketData_t configSocket =INITIALIZER_SSL_SOCKET_DATA;


    MockResponseExpected = "\r\n+QSSLSTATE: 3,\"SSLClient\",\"10.106.6.155\",0,5500,3,1,3,0,\"uart1\",1\r\n\r\nOK\r\n";

    configSocket.clientID = config.connectId = 3;
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(3, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("10.106.6.155",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(3,configSocket.state);

    configSocket.clientID = config.connectId = 11;
    MockResponseExpected = "\r\n+QSSLSTATE: 11,\"SSLClient\",\"192.168.32.68\",54842,5500,2,1,3,0,\"uart1\",1\r\n\r\nOK\r\n";
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("192.168.32.68",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(2,configSocket.state);
    
    configSocket.clientID = config.connectId = 11;
    MockResponseExpected = "AT+QSSLSTATE=11\r\r\n+QSSLSTATE: 3,\"SSLClient\",\"10.101.234.65\",0,2020,4,1,3,0,\"uart1\",1\r\n\r\nOK\r\n";
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(3, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("10.101.234.65",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(4,configSocket.state);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  

    memset(configSocket.locPort,0,8);

        configSocket.clientID = config.connectId = 11;
    MockResponseExpected = "AT+QSSLSTATE=11\r\r\nOK\r\n";
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(0,configSocket.state);
    TEST_ASSERT_EQUAL_INT(0,configSocket.serverID);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  

    configSocket.clientID = config.connectId = 11;
    MockResponseExpected = "AT+QSSLSTATE=11\r\r\n+QSSLSTATE: 11,\"SSLClient\",\"192.168.32.48\",54707,2020,4,1,3,0,\"uart1\",1\r\n\r\nOK\r\n";
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(4,configSocket.state);
    TEST_ASSERT_EQUAL_INT(3,configSocket.serverID);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));

        configSocket.clientID = config.connectId = 11;
    MockResponseExpected = "AT+QSSLSTATE=11\r\r\n+QSSLSTATE: 11,\"SSLClient\",\"192.168.32.48\",54707,2020,4,1,5,0,\"uart1\",1\r\n\r\nOK\r\n";
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(4,configSocket.state);
    TEST_ASSERT_EQUAL_INT(5,configSocket.serverID);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));

    
    configSocket.clientID = config.connectId = 11;
    MockResponseExpected ="QIURC: \"recv\",11\r\nAT+QSSLSTATE=11\r\r\n+QSSLSTATE: 11,\"SSLClient\",\"192.168.32.48\",55647,2020,2,1,3,0,\"uart1\",1\r\n\r\nOK\r\n";
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(11, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("192.168.32.48",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(2,configSocket.state);
    TEST_ASSERT_EQUAL_INT(3,configSocket.serverID);
    TEST_ASSERT_EQUAL_INT(1, cmIsAsyncEvent(&cmData));
    cmClearAllAsyncEvent(&cmData);

    configSocket.clientID = config.connectId = 2;
    MockResponseExpected = "\"192.168.32.48\",62538\r\nAT+QSSLSTATE=2\r\r\n+QSSLSTATE: 2,\"SSLClient\",\"10.101.234.65\",0,9999,3,1,2,0,\"uart1\",1\r\n\r\nOK\r\n"; 
    retValue = cellModem_SSLSocketGetStatus(&cmData,&configSocket);

    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(2, configSocket.clientID);
    TEST_ASSERT_EQUAL_STRING("10.101.234.65",configSocket.servAddr);
    TEST_ASSERT_EQUAL_INT(3,configSocket.state);
    TEST_ASSERT_EQUAL_INT(2,configSocket.serverID);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));

}

void test_modem_SSLSocketOpen(){
    cmError_t retValue = CM_FAIL;

    SSLSocketData_t configSocket =INITIALIZER_SSL_SOCKET_DATA;
    MockResponseExpected = CM_CMD_MOCK_QIOPEN_RESPONSE;
    configSocket.accessMode = 0;
    configSocket.pdpCtxID = 1;
    configSocket.clientID = 3;
    strcpy(configSocket.servAddr , "10.101.234.41");
    strcpy(configSocket.serverPort , "2020");
    
    cmClearAllAsyncEvent(&cmData);
    retValue = cellModem_SSLSocketOpen(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT(0, cmIsAsyncEvent(&cmData));  
    
}

void test_modem_SSLSocketClose(){
    cmError_t retValue = CM_FAIL;
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    retValue = cellModem_SSLSocketClose(&cmData,10);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
}


void test_modem_SSLSocketGetRecv(){
    char bufferRecv[CM_BUFFER_LEN_DEF] ;


    cmError_t retValue = CM_FAIL;
    cellModemConfig_t config =CELLMODEMCONFIG_INITIALIZER;
    SSLSocketData_t configSocket =INITIALIZER_SSL_SOCKET_DATA;
    configSocket.msgRecv = bufferRecv;
    //configSocket.buffRcvLen = CM_BUFFER_LEN_DEF;
   MockResponseExpected ="\r\n+QSSLRECV: 6\r\njulian\r\n\r\nOK\r\n";


    configSocket.clientID = config.connectId = 3;
    retValue = cellModem_SSLSocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(6, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("julian",configSocket.msgRecv);

  
   // memset(bufferRecv,0,sizeof(bufferRecv));
    MockResponseExpected = "\r\n+QSSLRECV: 112\r\n7EA036610330A166E6E7006128A109060760857405080102A203020101A305A10302010DBE0F040D0800065F04001802201388FA0074EA7E\r\n\r\nOK\r\n";

    configSocket.clientID = config.connectId = 11;
    
    retValue = cellModem_SSLSocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(112, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA036610330A166E6E7006128A109060760857405080102A203020101A305A10302010DBE0F040D0800065F04001802201388FA0074EA7E",configSocket.msgRecv);

    MockResponseExpected = "\r\n+QSSLRECV: 0\r\n\r\nOK\r\n";
    configSocket.clientID = config.connectId = 3;
    retValue = cellModem_SSLSocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(0, configSocket.msgLen);
    //TEST_ASSERT_EQUAL_STRING(" ",configSocket.msgRecv);

    MockResponseExpected = "AT+QSSLRECV=10,1500\r\r\n+QSSLRECV: 6\r\njulian\r\n\r\nOK\r\n";
    configSocket.clientID = config.connectId = 10;
    retValue = cellModem_SSLSocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(6, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("julian",configSocket.msgRecv);

    MockResponseExpected = "\r\n+QSSLRECV: 246\r\n" "Buenas a todos! Estaba chusmeando el proyecto. Los navigation devices esten teniendo un conjunto de posiciones, que se espera hacer con eso? Ponemos todas las posiciones en el mapa, hacemos un calculo en el front, que representan esas posiciones?" "\r\n\r\nOK\r\n";
    configSocket.clientID = config.connectId = 3;
    retValue = cellModem_SSLSocketGetRecv(&cmData,&configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK,retValue);
    TEST_ASSERT_EQUAL_INT32(246, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("Buenas a todos! Estaba chusmeando el proyecto. Los navigation devices esten teniendo un conjunto de posiciones, que se espera hacer con eso? Ponemos todas las posiciones en el mapa, hacemos un calculo en el front, que representan esas posiciones?",configSocket.msgRecv);

/*
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    configSocket.recvHexString = 1;
    retValue = cellModem_SocketDataFormat(&cmData,configSocket.recvHexString);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);

    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_HEX_STR;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData, &configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    TEST_ASSERT_EQUAL_INT32(18, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA02100020023037E", configSocket.msgRecv);

    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    configSocket.recvHexString = 1;
    retValue = cellModem_SocketDataFormat(&cmData,configSocket.recvHexString);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);

    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_HEX_STR_LARGE;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData, &configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    TEST_ASSERT_EQUAL_INT32(70, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA0210002002303939A7481801205018006018007040000000108040000000341187E", configSocket.msgRecv);
    
    unsigned char buffHex[512] ={0};
    unsigned char buffExpected[512]={0x7E, 0xA0,0x21 ,0x00 ,0x02 ,0x00 ,0x23 ,0x03 ,0x93 ,0x9A ,0x74 ,0x81 ,0x80 ,0x12 ,0x05 ,0x01 ,0x80 ,0x06 ,0x01 ,0x80 ,0x07 ,0x04 ,0x00 ,0x00 ,0x00 ,0x01 ,0x08 ,0x04 ,0x00 ,0x00 ,0x00 ,0x03 ,0x41 ,0x18 ,0x7E};
    int val = cellModem_StrToHexBuffer(configSocket.msgRecv,buffHex, (int)configSocket.msgLen);
    TEST_ASSERT_GREATER_THAN_INT16(0,val);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(buffExpected,buffHex,configSocket.msgLen);

    //disable recv hexstr
    MockResponseExpected = CM_CMD_MOCK_GENERAL_RESPONSE;
    configSocket.recvHexString = 0;
    retValue = cellModem_SocketDataFormat(&cmData,configSocket.recvHexString);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    
    MockResponseExpected = CM_CMD_MOCK_QIRD_RESPONSE_LONG;
    configSocket.connectId = config.connectId = 3;
    retValue = cellModem_SocketGetRecv(&cmData, &configSocket);
    TEST_ASSERT_EQUAL_INT32(CM_OK, retValue);
    TEST_ASSERT_EQUAL_INT32(112, configSocket.msgLen);
    TEST_ASSERT_EQUAL_STRING("7EA036610330A166E6E7006128A109060760857405080102A203020101A305A10302010DBE0F040D0800065F04001802201388FA0074EA7E", configSocket.msgRecv);
*/
   }

/*=========================================================
                    Wrappers
 ==========================================================
*/

//---systick generator-----------------------------------------------------
uint32_t GetTickCountMs(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)(ts.tv_nsec / 1000000) + ((uint32_t)ts.tv_sec * 1000);
}

//-----------uart tx mock -------------------------------------------------
void OutputFunction( void *sp, char c){
	int i = 0; 
    (void)sp;
   // char ResponseExpected[100] = {CM_CMD_MOCK_ATI_RESPONSE};//{CM_CMD_MOCK_GENERAL_RESPONSE};
	if(c != '\r')
    	printf(KYEL "%c",c); /*no print \r in console */
	
	if(c == '\r') {	 /*if send command to module*/
		printf(KWHT); /*black color */
       
        while(MockResponseExpected[i] != '\0') { /*then the module response is pass to isr char by char */
		 	// para nonblocking test colocar un wait pequeño
            cellModem_IsrRx(&cmData, MockResponseExpected[i]); 
			i++;
		}
        /*print command and response*/
        printf(" -->");
		printf(KGRN "%s",MockResponseExpected);  
        printf(KNRM); /*white color */
	}
}