#include "songlistproxy.h"
#include "songlistbroker.h"
#include "songbroker.h"
#include "songproxy.h"
#include "json/json.h"
#include <iostream>

std::string SongListProxy::songListInformation(std::string songId){
    auto songListBroker = SongListBroker::getInstance();
    auto res =songListBroker->findSongList(songId);

    Json::Value root;
    Json::Value arryObj;
    root["type"] = "SONGLIST";
    if(res == NULL){
        root["hasData"] = "no";
        return root.toStyledString();
    }else{
        root["id"] = res->getId();
        root["name"] = res->getName();
        root["author"] = res->getAuthor();
        root["createTime"] = res->getCreateTime();
        root["label"] = res->getLabel();
        root["info"] = res->getInfo();
        root["icon"] =res->getIcon();
        root["collectionQuantity"] = res->getCollectionQuantity();
        root["clickQuantity"] = res->getClickQuantity();
        root["shareQuantity"] = res->getShareQuantity();

        auto map = res->getSongs();
        for(auto iter = map.begin(); iter != map.end(); iter++) {
             Json::Value item;
             item["id"] = iter->second->getId();
             item["name"] = iter->second->getName();
             item["source"] = iter->second->getSource();
             item["singer"] = iter->second->getSinger();
             item["album"] = iter->second->getAlbum();
             item["playQuantity"] = iter->second->getPlayQuantity();
             item["downloadQuantity"] = iter->second->getDownloadQuantity();
             item["shareQuantity"] = iter->second->getShareQuantity();
             arryObj.append(item);
         }
        root["array"] = arryObj;
        return root.toStyledString();
    }
}
