#include <iostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"


int main()
{
    // 读取JSON的示例
    std::cout<<"------------------------- parse demo --------------------"<<std::endl;

/*
   {
	"coutry": "china",
	"area": 960,
	"developed": false,
	"nationalities": ["汉族", "藏族", "傣族"],
	"provinces": [{
		"province": "安徽",
		"short": "皖"
	}, {
		"province": "浙江",
		"short": "浙"
	}],
	"capital": {
		"name": "北京",
		"population": 2170.7
	}
  }
*/ 
    std::string json = "{\"coutry\":\"china\",\"area\":960,\"developed\":false,\"nationalities\":[\"汉族\",\"藏族\",\"傣族\"],\"provinces\":[{\"province\":\"安徽\",\"short\":\"皖\"},{\"province\":\"浙江\",\"short\":\"浙\"}],\"capital\":{\"name\":\"北京\",\"population\":2170.7}}";

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    //出错处理
    if(doc.HasParseError() == true){
        rapidjson::ParseErrorCode code = doc.GetParseError(); //解析的错误码
        size_t offset = doc.GetErrorOffset(); //错误的位置       
        std::cout<<"json invalid, code="<<code<<", offset="<<offset<<std::endl;
        return 0;
    }

    //解析基本字段
    if(doc.HasMember("coutry") && doc["coutry"].IsString()){
        std::string coutry = doc["coutry"].GetString();
        std::cout<<"coutry:"<<coutry<<std::endl;
    }

    if(doc.HasMember("area") && doc["area"].IsUint()){
        unsigned int area = doc["area"].GetUint();
        std::cout<<"area:"<<area<<std::endl;;
    }

    if(doc.HasMember("developed") && doc["developed"].IsBool()){
        bool developed = doc["developed"].GetBool();
        std::cout<<"developed:"<<(developed ? "true":"false")<<std::endl;;
    }

    //解析数组 - 简单
    if(doc.HasMember("nationalities") && doc["nationalities"].IsArray()){

        rapidjson::Value& valueNationalities = doc["nationalities"];
        for(size_t i = 0; i < valueNationalities.Size(); i++){
            rapidjson::Value& valueNationality = valueNationalities[i];
            if(valueNationality.IsString()){
                std::string nationality = valueNationality.GetString();
                std::cout<<"nationality:"<<nationality<<std::endl;
            }
        }
    }

     //解析数组 - 复杂
    if(doc.HasMember("provinces") && doc["provinces"].IsArray()){
        
        rapidjson::Value& valueProvinces = doc["provinces"];
        for(size_t i = 0; i < valueProvinces.Size(); i++){
            rapidjson::Value& valueProvince= valueProvinces[i];
            if( valueProvince.HasMember("province") && valueProvince["province"].IsString() &&
                valueProvince.HasMember("short") && valueProvince["short"].IsString() 
            ){
                std::string province = valueProvince["province"].GetString();
                std::string sht = valueProvince["short"].GetString();
                std::cout<<"province:"<<province<<", short:"<<sht<<std::endl;
            }
        }
    }

    //解析嵌套json
    if(doc.HasMember("capital") && doc["capital"].IsObject()){

        rapidjson::Value& valueCapital = doc["capital"];
        if(valueCapital.HasMember("name") && valueCapital["name"].IsString()){
            std::string name = valueCapital["name"].GetString();
            std::cout<<"capital name:"<<name<<std::endl;
        }

        if(valueCapital.HasMember("population") && valueCapital["population"].IsDouble()){
            double population = valueCapital["population"].GetDouble();
            std::cout<<"capital population:"<<population<<"万"<<std::endl;
        }
    }

    // 生成JSON的示例
    std::cout<<"------------------------- create demo --------------------"<<std::endl;

    rapidjson::Document wdoc; //doc for write
    rapidjson::Document::AllocatorType &allocator = wdoc.GetAllocator();
    wdoc.SetObject();

    //基本字段
    wdoc.AddMember("coutry","china",allocator);
    wdoc.AddMember("area",960,allocator);
    wdoc.AddMember("developed",false,allocator);

    //数组 - 简单
    rapidjson::Value nationalities(rapidjson::kArrayType);
    nationalities.PushBack("汉族",allocator);
    nationalities.PushBack("藏族",allocator);
    nationalities.PushBack("傣族",allocator);
    wdoc.AddMember("nationalities",nationalities, allocator);

    //数组 - 复杂
    rapidjson::Value provinces(rapidjson::kArrayType);

    rapidjson::Value anhui(rapidjson::kObjectType);
    anhui.AddMember("province", "安徽", allocator);
    anhui.AddMember("short", "皖", allocator);
    provinces.PushBack(anhui, allocator);

    rapidjson::Value zhejiang(rapidjson::kObjectType);
    zhejiang.AddMember("province", "浙江", allocator);
    zhejiang.AddMember("short", "浙", allocator);
    provinces.PushBack(zhejiang, allocator);

     wdoc.AddMember("provinces",provinces, allocator);

    //嵌套json
    rapidjson::Value capital(rapidjson::kObjectType);
    capital.AddMember("name","北京",allocator);
    capital.AddMember("population", "2170.7", allocator);
    wdoc.AddMember("capital",capital,allocator);

    //生成json string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    wdoc.Accept(writer);

    std::string wjson = buffer.GetString();
    std::cout<<"json: "<<wjson<<std::endl;
}
