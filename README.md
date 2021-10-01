# ETS2 Controller with Arduino

##### KOR
이 프로젝트는 실제 차량의 부품을 이용하여 유로트럭 시뮬레이터 컨트롤러를 제작하는 과정입니다.
사용한 부품은 모두 현대 2010년식 투싼ix에 사용되는 부품을 토대로 제작했습니다.
컴퓨터와 아두이노의 직접연결은 USB로 통신을 하게 되며 만약 컨트롤러를 자체제작하고 싶으시다면, 사용할 부품을 가진 차량의 회로도를 찾아서 각 핀이 어떤 역할을 하는지 확인하시고 그에 따라 코딩하시면 됩니다.

##### ENG
This code is made for ETS2 controler with parts of real cars.
If you want to use this code in your hardware, you have to make a pinmap and set pins where they should be.
I made this code and hardware with the parts those are in Tuxcan ix since 2010 of Hyundai.
I refered to the pinmap of each part, and made the map of connection with arduino and connector of the parts.

***

## Make a PINMAP

If you want to see the pinmap of the part you have, you can see that in google.
I got the map in [GSW(Global Service Way - Technical Information)](https://gsw.hyundai.com).

### Pin Map

***

#### Multi-Function Switch (Connector : M20-L, M20-W)

##### M20-L(Light switch connector)
![AnyConv com__5xsf7ypp](https://user-images.githubusercontent.com/81617707/130624823-6ad2b161-9b47-467c-9855-873a33e59208.jpg)

Pin number | When signal is HIGH
---------- | -----
1 | Tail lamp ON
2 | Ground of light switch
3 | Autolight ON **(unavailable)**
4 | Head lamp ON
5 | Ground of fog lamp
6 | Fog lamp on/off
7 | *(**_Unconnected_**)
8 | Head lamp LO state
9 | Head lamp HI state
10 | Head lamp state switch input
11 | Left turnsignal ON
12 | Main power of turnsignal switch
13 | Right turnsignal ON

##### M20-W(Washer switch connector)
![AnyConv com__2mp09htt](https://user-images.githubusercontent.com/81617707/130625074-c7b136cf-a74c-4ebd-96c7-9d39599c2efe.jpg)

Pin number | When signal is HIGH
---------- | -----
1 | Mist state ON
2 | Ground of front washer switch
3 | Front wipers LO state
4 | Ground of front wipers INT speed
5 | Front wipers of INT speed value output **(Analog Output)**
6 | Rear wiper ON
7 | Rear wiper INT ON
8 | Front wipers INT state
9 | Front wipers HI state
10 | Main power of front wipers & washer switch
11 | Front washer ON
12 | Main power of rear wiper & washer switch
13 | Rear washer ON
14 | *(**_Unconnected_**)

***

#### Key box switch (Connector : M18)

##### M18
![mcmy21ff](https://user-images.githubusercontent.com/81617707/131852206-84e84e29-8451-4cf9-9730-7815e3f133ea.jpg)

Pin number | When signal is HIGH
-----------| -----------
1 | Main power input of the switch
2 | Key is ON state
3 | Key is Start state
4 | Key is from ON state to Start state
5 | Main power input of the switch
6 | Key is from ACC state to ON state

***

## Set virtual joystick buttons
ETS2 support this buttons.
* Turn on/off Left/Right Turnsignal
* Turn on/off Hazard light
* Turn on/off Head light(only it works off-tail light-headlight)
* Turn on/off high beam
* Turn on/off passing light
* Increase wiper speed
* Decrease wiper speed

## Design the circit
When you make the pinmap exactly, then you'll design the circit of the controller. you should know how pull-up switch and pull-down switch work. You should look the schematic of switchs and decide switch type of your circit.

## Reference of the code

I refered the library of [ArduinoJoystickLibrary made by MHeironimus](https://github.com/MHeironimus/ArduinoJoystickLibrary).
You __HAVE TO install__ the Arduino library in your environment, if you want refer my code.

