#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME monopoly)

project(${APP_NAME})

if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif()
endif()

if(NOT DEFINED BUILD_ENGINE_DONE) # to test monopoly into root project
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/ZH.cpp

     Classes/Character/Character.cpp
     Classes/Character/Dice.cpp

     Classes/God/Angel.cpp
     Classes/God/Earth.cpp
     Classes/God/Luck.cpp
     Classes/God/Poor.cpp
     Classes/God/Unluck.cpp
     Classes/God/Devil.cpp
     Classes/God/God.cpp
     Classes/God/MinePosition.cpp
     Classes/God/Rich.cpp

     Classes/Incident/Criminal.cpp
     Classes/Incident/Finance.cpp
     Classes/Incident/Incident.cpp
     Classes/Incident/Realtor.cpp
     Classes/Incident/Stay.cpp
     Classes/Incident/Economy.cpp
     Classes/Incident/Holiday.cpp
     Classes/Incident/Medical.cpp
     Classes/Incident/Staff.cpp

     Classes/Item/AngelCard.cpp
     Classes/Item/ControlDice.cpp
     Classes/Item/HouseChange.cpp
     Classes/Item/Item.cpp
     Classes/Item/Pray.cpp
     Classes/Item/RidHospital.cpp
     Classes/Item/Sleep.cpp
     Classes/Item/Turtle.cpp
     Classes/Item/Average.cpp
     Classes/Item/DevilCard.cpp
     Classes/Item/HouseDestory.cpp
     Classes/Item/Mine.cpp
     Classes/Item/RedCard.cpp
     Classes/Item/RidJail.cpp
     Classes/Item/Stop.cpp
     Classes/Item/Worker.cpp
     Classes/Item/BlackCard.cpp
     Classes/Item/Escape.cpp
     Classes/Item/HouseExchange.cpp
     Classes/Item/Missile.cpp
     Classes/Item/Revenge.cpp
     Classes/Item/RisePrice.cpp
     Classes/Item/Transmit.cpp
     Classes/Item/Car.cpp
     Classes/Item/Frame.cpp
     Classes/Item/Impute.cpp
     Classes/Item/Motor.cpp
     Classes/Item/RidGod.cpp
     Classes/Item/Robot.cpp
     Classes/Item/TurnAround.cpp

     Classes/Land/Aviation.cpp
     Classes/Land/Business.cpp
     Classes/Land/Enterprise.cpp
     Classes/Land/Hotel.cpp
     Classes/Land/Insurance.cpp
     Classes/Land/Land.cpp
     Classes/Land/Lottery.cpp
     Classes/Land/Oil.cpp
     Classes/Land/Resort.cpp
     Classes/Land/Bank.cpp
     Classes/Land/Chance.cpp
     Classes/Land/Hospital.cpp
     Classes/Land/Institute.cpp
     Classes/Land/Jail.cpp
     Classes/Land/Life.cpp
     Classes/Land/Mall.cpp
     Classes/Land/Park.cpp
     Classes/Land/Technology.cpp

     Classes/Scene/BankScene.cpp
     Classes/Scene/IncidentScene.cpp
     Classes/Scene/MapScene.cpp
     Classes/Scene/SettingScene.cpp
     Classes/Scene/StorkScene.cpp
     Classes/Scene/ExchangeScene.cpp
     Classes/Scene/LotteryScene.cpp
     Classes/Scene/SelectScene.cpp
     Classes/Scene/StartScene.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/ZH.h

     Classes/Character/Character.h
     Classes/Character/Dice.h

     Classes/God/Angel.h
     Classes/God/Earth.h
     Classes/God/Luck.h
     Classes/God/Poor.h
     Classes/God/Unluck.h
     Classes/God/Devil.h
     Classes/God/God.h
     Classes/God/MinePosition.h 
     Classes/God/Rich.h

     Classes/Incident/Criminal.h
     Classes/Incident/Finance.h
     Classes/Incident/Incident.h
     Classes/Incident/Realtor.h
     Classes/Incident/Stay.h
     Classes/Incident/Economy.h
     Classes/Incident/Holiday.h
     Classes/Incident/Medical.h
     Classes/Incident/Staff.h

     Classes/Item/AngelCard.h
     Classes/Item/ControlDice.h
     Classes/Item/HouseChange.h
     Classes/Item/Item.h
     Classes/Item/Pray.h
     Classes/Item/RidHospital.h
     Classes/Item/Sleep.h
     Classes/Item/Turtle.h
     Classes/Item/Average.h
     Classes/Item/DevilCard.h
     Classes/Item/HouseDestory.h
     Classes/Item/Mine.h
     Classes/Item/RedCard.h
     Classes/Item/RidJail.h
     Classes/Item/Stop.h
     Classes/Item/Worker.h
     Classes/Item/BlackCard.h
     Classes/Item/Escape.h
     Classes/Item/HouseExchange.h
     Classes/Item/Missile.h
     Classes/Item/Revenge.h
     Classes/Item/RisePrice.h
     Classes/Item/Transmit.h
     Classes/Item/Car.h
     Classes/Item/Frame.h
     Classes/Item/Impute.h
     Classes/Item/Motor.h
     Classes/Item/RidGod.h
     Classes/Item/Robot.h
     Classes/Item/TurnAround.h

     Classes/Land/Aviation.h
     Classes/Land/Business.h
     Classes/Land/Enterprise.h
     Classes/Land/Hotel.h
     Classes/Land/Insurance.h
     Classes/Land/Land.h
     Classes/Land/Lottery.h
     Classes/Land/Oil.h
     Classes/Land/Resort.h
     Classes/Land/Bank.h
     Classes/Land/Chance.h
     Classes/Land/Hospital.h
     Classes/Land/Institute.h
     Classes/Land/Jail.h
     Classes/Land/Life.h
     Classes/Land/Mall.h
     Classes/Land/Park.h
     Classes/Land/Technology.h

     Classes/Scene/BankScene.h
     Classes/Scene/IncidentScene.h
     Classes/Scene/MapScene.h
     Classes/Scene/SettingScene.h
     Classes/Scene/StorkScene.h
     Classes/Scene/ExchangeScene.h
     Classes/Scene/LotteryScene.h
     Classes/Scene/SelectScene.h
     Classes/Scene/StartScene.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if(MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif(IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
