#include "dataprocess.h"

//数据解析 兼容匿名上位机..
typedef enum
{
    COMM_DATA_CAM_UNKNOWN = 0,//未知
    COMM_DATA_CAM_GRAYSCALE8,//相机 8位灰度
    COMM_DATA_CAM_GRAYSCALE1,//相机 1位灰度
    COMM_DATA_SYS_SPEED,//系统运行速率 (函数实际频率)
    COMM_DATA_CAR_RUNNING,//小车运行数据..
    COMM_DATA_CAR_SENSOR,//传感器数据
    COMM_DATA_CAR_PWM,//小车PWM数据
    COMM_DATA_UPPER_PID,//更新PID数据..双向设定..
    COMM_DATA_SETTING,//对车进行设置(各种开关)
    COMM_DATA_OTHER//根据表中的设定自行匹配
}COMM_DATATYPE_e;

typedef enum
{
    COMM_STATUS_IDLE = static_cast<uint8_t>(0),//应该可以用常量表达式转换
    COMM_STATUS_HEAD = 0xAA,//0xAA
    COMM_STATUS_SADDR,//0x66 0x77 四轮,直立
    COMM_STATUS_DADDR = 0xBF,//0xBF bins UpperMonitor
    COMM_STATUS_TYPE,//Type enum typeDef
    COMM_STATUS_LEN,//Data Length
    COMM_STATUS_DATA,//Data main
    COMM_STATUS_CHECK,//CheckNum
    COMM_STATUS_END
}COMM_PARSE_STATUS_e;

typedef struct{
    COMM_PARSE_STATUS_e status;
    COMM_DATATYPE_e type;
    uint16_t packageSize;//数据长度..
    uint16_t dataSize;
    uint16_t toFillSize;//填充大小
    uchar* dataPtr;
}COMM_DATA_TypeDef;



DataProcess::DataProcess(QObject *parent) : QObject(parent)
{

}

DataProcess::~DataProcess()
{

}

bool DataProcess::checkData()
{
    return false;
}

static COMM_DATA_TypeDef commData = {COMM_STATUS_IDLE,COMM_DATA_CAM_UNKNOWN,0, 0, 0,nullptr};

bool DataProcess::ProcessPackage(QByteArray &byteArray)
{
    QByteArray *byteData = &byteArray;
    int size = byteData->size();

    //取得首地址..这里需要解决一下问题
    const uchar* dataPtr = (const uchar*)byteData->constData();

    do{
        switch(commData.status){
        case COMM_STATUS_IDLE:
            if(COMM_STATUS_HEAD == *dataPtr)
            {
                commData.status = COMM_STATUS_HEAD;
            }else{
                commData.status = COMM_STATUS_IDLE;
            }
            dataPtr++;
            break;

        //上一步已经判断了header
        case COMM_STATUS_HEAD:
            dataPtr++;
            commData.status = COMM_STATUS_SADDR;
            break;

        case COMM_STATUS_SADDR://直接查找目的地址
            if(COMM_STATUS_DADDR == *dataPtr)
            {
                commData.status = COMM_STATUS_TYPE;
            }else{
                commData.status = COMM_STATUS_IDLE;
            }
            dataPtr++;
            break;

        case COMM_STATUS_TYPE:
            //决定type type限定..
            commData.type = (COMM_DATATYPE_e)*dataPtr;
            commData.status = COMM_STATUS_LEN;
            dataPtr++;
            //qDebug()<<commData.type;
            break;




        default:
            break;
        }
    }while(size >= 0);
}
