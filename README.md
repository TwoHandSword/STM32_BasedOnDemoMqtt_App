STM32CubeExpansion_Cloud_AWS_V2.0.0 기반의 프로젝트

프로젝트 원본은 STM 홈페이지에서 다운로드 가능 https://www.st.com/en/evaluation-tools/b-l4s5i-iot01a.html#tools-software

1. 이 저장소는 데모 프로젝트의 모든 파일이 아니라 데모 프로젝트 내의 Applications\Cloud\asw_demos 폴더만 관리한다.
2. 이 폴더만 가지고는 빌드가 되지 않으므로, https://github.com/TwoHandSword/STM32_BasedOnDemoMqtt_Bsw 저장소 파일을 내려받아서 같이 빌드해야한다.
3. https://github.com/TwoHandSword/STM32_BasedOnDemoMqtt_Bsw -> 이 저장소는 C:\ 에 설치하고
4. 이 저장소는 C:\STM32CubeExpansion_Cloud_AWS_V2.0.0\Projects\B-L4S5I-IOT01A\Applications\Cloud\asw_demos에 설치해서 빌드해야한다.
5. 이 저장소 커밋할때 버전관리가 Bv001_Av001_C1 이런식으로 네이밍 할 건데,  Bv의 의미는 STM32_BasedOnDemoMqtt_Bsw 저장소의 SW 버전을 의미하고
    Av는 본 저장소의 SW 버전을 의미한다.  C는 코드변경은 아닌데 내용변경등을 나타내기 위함이다.(Comment약자)
	
#0
Projects\B-L4S5I-IOT01A\Applications\Cloud\aws_demos\config_files 경로에 있는
aws_demo_config.h 파일에서 CONFIG_XXX_DEMO_ENABLED 라는 형태의 10개의 #define 문을 사용해서 해당 프로젝트의 동작 모드를 결정할 수 있다.(한번에 1개 모드만 Enable해야함)
이 프로젝트는 10개의 데모 동작 중에서 CONFIG_MQTT_DEMO_ENABLED 모드를 Base로 하여 개발하기 시작함

#1
Middlewares/Third_Party/amazon-freetos/demos/include 경로에 있는
aws_clientcredential.h  파일에서 
wifi ssid, password, security type , aws-core REST API , Thing name 정의해서 사용한다.
실제 코드에서 사용하는 Define 문의 이름은 아래와 같음
clientcredentialWIFI_SSID , clientcredentialWIFI_PASSWORD, clientcredentialWIFI_SECURITY, clientcredentialMQTT_BROKER_ENDPOINT , clientcredentialIOT_THING_NAME

위 코드는 STM32CubeExpansion_Cloud_AWS_V2.0.0 에서 다운로드 받은 SW안에 포함되어있고, 여기 Repository에 이 코드는 올라가지 않음


#2 21.12.18
Initial code Upload
**유의사항 1** : STM32CubeExpansion_Cloud_AWS_V2.0.0 파일 ST 홈페이지에서 다운로드 한 후 압축 풀어서 코드 놔두는 경로를 반드시 C드라이브에 바로 푼다
    C:\STM32CubeExpansion_Cloud_AWS_V2.0.0
**유의사항 2** : 깃허브에 올라와있는 코드는 aws_demos라는 폴더인데 . 이 폴더를 반드시 아래의 경로에 넣어놓고 사용할 것
깃허브에 올라와있는 파일만 받아서는 빌드가 안된다. STM32CubeExpansion_Cloud_AWS_V2.0.0 폴더 안에 들어있는 각종 라이브러리 등등을 활용해서 같이 빌드하도록 IDE 환경이 구성돼있기 때문이다.
C:\STM32CubeExpansion_Cloud_AWS_V2.0.0\Projects\B-L4S5I-IOT01A\Applications\Cloud\aws_demos
**유의사항 3**
CubeIde에서 프로젝트 import 하는 경로를
C:\STM32CubeExpansion_Cloud_AWS_V2.0.0\Projects\B-L4S5I-IOT01A\Applications\Cloud\aws_demos 로 해서 사용하면 된다.

**필독 참고사항**
aws_demos 폴더에는 Proj_ForHwCfgCodeGen 라는 폴더가 포함돼있는데 이것은 Cube Ide에서 만든 별도의 프로젝트 폴더다.
이 프로젝트폴더의 목적은 aws_demo 프로젝트에는 hw를 cubemx로 configure 해서 code gen 하는 .ioc파일이 없어서, 그것을 만들기 위한 것이다.

aws_demos\Proj_ForHwCfgCodeGen\Core\Inc 경로안에 있는 .h 파일 중에.
es_wifi_conf.h , es_wifi_io.h , flash.h , watchdogkicker.h 4개 파일은 원래 demo project에 있던걸 복사붙여놓기로 이쪽으로 옮겨놓은 것이고
main.h , stm32l4xx_hal_conf.h , stm32l4xx_it.h  3개의 파일은 해당 프로젝트의 .ioc 파일을 codegen하면 업데이트되는 헤더파일이다.
demo project에서 빌드 할 때 이 header file을을 include 하여 빌드를 해야 하기 때문에,  demo project의 inclue path에 aws_demos\Proj_ForHwCfgCodeGen\Core\Inc 를 추가해두었다.

aws_demos\Proj_ForHwCfgCodeGen\Core\Inc 경로안에 있는 .c파일들이 여러개 있는데
main.c , stm32l4xx_hal_msp.c  , stm32l4_xx_it.c 이 3개의 파일을 demo project에서 가져다가 사용한다.
이 3개 파일 외에 다른 파일들도 .ioc에 의해 code gen이 되지만 이런저런 이유로 demo project에서 가져다가 사용하지는 않는다.
ex) stm32l4xx_hal_timebase_tim.c 파일의 경우 .ioc 파일에 의해서 generate 되지만 demo project에서는 활용되지않는다. 
demo project에서는 aws_demos\Src 폴더 안에 있는 stm32l4xx_hal_timebase_tim.c 를 빌드에 사용한다.

헷갈릴 수 있는데 다시 정리하면
원래 홈페이지에서 다운로드 받은 원본프로젝트 압축을 풀어보면 아래와 같은 2개의 폴더가 존재하고
aws_demos/Inc
asw_demos/Src
위 폴더에 있는 .c 파일과 .h 파일을 aws_demo 프로젝트에서 빌드할때 사용한다.

근데 여기 repository에 있는 프로젝트에서는 아래 6개 파일들을
main.h , stm32l4xx_hal_conf.h , stm32l4xx_it.h
main.c , stm32l4xx_hal_msp.c  , stm32l4_xx_it.c

aws_demos/Inc   =>   aws_demos\Proj_ForHwCfgCodeGen\Core\Inc
asw_demos/Src  =>    aws_demos\Proj_ForHwCfgCodeGen\Core\Src
에 있는걸 가져와서 빌드하도록 구성해놨다는 거다.
ppt 그림으로 좀 더 이해하기 쉽게 그려서 업로드하겠다.
프로젝트구조설명.pptx <-참고

22-01-08 오후3시52분
BSW쪽에서
Bv001_C1  aws iot thing의 이름/ End point / 와이파이 아이디 / 와이파이 비밀번호를 configure 관련 변경
관련 Configure를 원래 aws_clientcredential.h 에서 하는데 이렇게하면 app 단에서 수정하기가 불편해서 #include "My_ClientCredential.h 라는 파일을 inlcude 하도록 하고, 그 안에서 YHS_MY_xxx  형태로 Define 하도록했다.
해당 파일은 App 쪽에 추가될거고, 비밀번호와 연관돼있어서 App 쪽에서 git ignore 될 것이다.

App에 aws_demos\STM32CubeIDE\Application\My_Cridential 에 My_ClientCredential.h 파일을 추가했다.
여기에서 thing 이름, endpoint 와이파이아이디, 와이파이 비번 Configure 해줄 것이다. 근데 개인정보가 있어서 git에서는 ignore 했다.
해당 파일에서 아래 부분을 정의해줘야한다.

#define YHS_MY_ENDPOINT     	 ""
#define YHS_MY_THING      		 ""
#define YHS_MY_WIFI_SSID        ""
#define YHS_MY_WIFI_PASSWORD    ""
	
