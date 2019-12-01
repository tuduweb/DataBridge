#include "dataprocess.h"

#include <QDebug>


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
    uint8_t check = 0;//校验

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

        case COMM_STATUS_LEN:
            //拼接大小..
            commData.dataSize = (uint16_t)((*dataPtr++)<<8);
            commData.dataSize += *(dataPtr++);
            size--;//这里解析了两个.. 所以要多减掉一个大小
            //dataPtr+=2;
            if(commData.dataSize == 0)
            {
                commData.status = COMM_STATUS_IDLE;
            }else{
                //待填充的数据大小..
                commData.toFillSize = commData.dataSize;
                //开辟一个新的连续的数据地址块..存储包实际数据.
                commData.dataPtr = new uchar[commData.dataSize];//这里是原始数据.需要保存 or 删除掉..
                commData.status = COMM_STATUS_DATA;
            }
            break;

        case COMM_STATUS_DATA:
        //解析数据
            if(commData.toFillSize <= size)
            {
                //填充
                memcpy(commData.dataPtr + commData.dataSize - commData.toFillSize,dataPtr,commData.toFillSize);
                dataPtr+=commData.toFillSize;//指针指向了最后..
                //总大小 - 已经填充大小 <= 剩余的长度.那么本次可以填充完数据.执行填充数据..
                size -= commData.toFillSize;//剩余包的大小 当前大小 - 本次会填充的大小
                commData.toFillSize = 0;//剩余填充0
                //delete []commData.dataPtr;
                commData.status = COMM_STATUS_CHECK;
                //emit 开始解析...

                //ProcessPackage(&commData);
            }else{
                //本次没办法填充完.那么把剩余的内容全填充了.
                size_t t = size;
                memcpy(commData.dataPtr + commData.dataSize - commData.toFillSize,dataPtr,t);
                qDebug()<<QString("fill %1 %2").arg(commData.dataSize - commData.toFillSize).arg(size);
                //dataPtr+=size;//全部传输完毕 所以不需要指针移动了。指向末尾
                commData.toFillSize -= size;
                size = 0;
            }
            break;

        case COMM_STATUS_CHECK:
            //校验方法..需要单独弄出去
            for(int i =0;i<120;i++)
            {
                check += (*(uint8_t (*)[120][188])commData.dataPtr)[i][i + 34];
            }

            //数据校验..验证
            if(check != *dataPtr++)
            {
                commData.status = COMM_STATUS_IDLE;
            }else{
                commData.status = COMM_STATUS_END;
            }
            break;

            //结束符..如果没有结束符那还是有问题..我觉得可以不要结束符号..
        case COMM_STATUS_END:
            if(0xff == *dataPtr++)
            {
                //ProcessPackage(&commData);
            }
            //完成整个步骤.本数据解析实力重置到空闲状态..
            commData.status = COMM_STATUS_IDLE;

            break;


        default:
            break;
        }
    }while(--size >= 0);

    //...上面的步骤当没有新的数据包后,就会停止,等待下一次数据。

    //一个MTU包大概是1300字节左右. 1300*8
}
