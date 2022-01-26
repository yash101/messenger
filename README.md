# messenger
UDP-based messaging

## Protocol

```
client-------[udp]------>server: msg = hello message
client<------[udp]-------server: public key
client----[udp + rsa]--->server: encrypted: client aes256 key + iv
client<-[udp + aes256]--server: AES 256 encrypyed: server aes256 key + iv
```

* Messages consist of 1+ packets
* First packet consists of IV offset (AES256-CTR)
* First packet may contain md5 of message if requested
* Each packet contains a sequence number
* Each packet contains reliability information
