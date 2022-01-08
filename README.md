STM32CubeExpansion_Cloud_AWS_V2.0.0 기반의 프로젝트

프로젝트 원본은 STM 홈페이지에서 다운로드 가능 https://www.st.com/en/evaluation-tools/b-l4s5i-iot01a.html#tools-software

1. 이 저장소는 데모 프로젝트의 모든 파일이 아니라 데모 프로젝트 내의 Applications\Cloud\asw_demos 폴더만 관리한다.
2. 이 폴더만 가지고는 빌드가 되지 않으므로, https://github.com/TwoHandSword/STM32_BasedOnDemoMqtt_Bsw 저장소 파일을 내려받아서 같이 빌드해야한다.
3. https://github.com/TwoHandSword/STM32_BasedOnDemoMqtt_Bsw -> 이 저장소는 C:\ 에 설치하고
4. 이 저장소는 C:\STM32CubeExpansion_Cloud_AWS_V2.0.0\Projects\B-L4S5I-IOT01A\Applications\Cloud\asw_demos에 설치해서 빌드해야한다.
5. 이 저장소 커밋할때 버전관리가 Bv001_Av001_C1 이런식으로 네이밍 할 건데,  Bv의 의미는 STM32_BasedOnDemoMqtt_Bsw 저장소의 SW 버전을 의미하고
    Av는 본 저장소의 SW 버전을 의미한다.  C는 코드변경은 아닌데 내용변경등을 나타내기 위함이다.(Comment약자)
