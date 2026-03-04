# my_ping

## ICMP echo request/reply를 이용한 ping 구현


## 지원 옵션
| 옵션 | 인자 | 설명 |
|------|------|------|
| `-v` | - | Verbose 모드 |
| `-?` | - | 사용법 출력 |
| `-c` | count | 전송할 패킷 수 |
| `-i` | interval | 패킷 전송 간격 (초) |
| `-p` | pattern | 패딩 패턴 (hex) |
| `-s` | size | 페이로드 크기 |
| `-T` | tos | Type of Service |
| `--ttl` | ttl | Time To Live |

- [x] 프로젝트 구조 설계
- [x] 인자 파싱 시스템
  - [x] 테이블 기반 옵션 디스패치
  - [x] 숫자 파싱 (오버플로우 체크)
  - [x] Hex 패턴 파싱
- [x] 디버그 출력 기능
- [ ] 소켓 생성 (SOCK_RAW, IPPROTO_ICMP)
- [ ] DNS 이름 해석 (getaddrinfo)
- [ ] ICMP 패킷 구성
  - [ ] ICMP 헤더 구조체
  - [ ] 체크섬 계산
  - [ ] 시퀀스 번호 관리
- [ ] 패킷 송신 (sendto)
- [ ] 패킷 수신 (recvmsg)
- [ ] RTT 계산 (gettimeofday)
- [ ] 통계 출력
  - [ ] 패킷 손실률
  - [ ] min/avg/max/mdev
- [ ] 시그널 핸들링 (SIGINT → 통계 출력 후 종료)
- [ ] TTL 설정 (setsockopt)
- [ ] 에러 메시지 개선

## 🔧 빌드

| 명령어 | 설명 |
|--------|------|
| `make` | 빌드 |
| `make clean` | 오브젝트 파일 삭제 |
| `make fclean` | 전체 삭제 |
| `make re` | 재빌드 |