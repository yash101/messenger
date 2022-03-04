# Messenger protocol

```
+-----------------+
| 1 - packet type |
| 2 - length      |
| 0 - payload     |
+-----------------+
```

## Connection + Authentication

1. Client -> Server
    - Packet type: 0x00 - hello
    - length: 0
    - Payload: NULL
2. Server -> Client
    - Packet type: 0x00 - hello
    - Length: {public key + signature size}
    - Payload: RSA public key
3. Client -> Server
    - Packet type: 0x01 - authenticate
    - Length: RSA block with random 
    - Payload: AES 256 key, encrypted via RSA

## Message

### Packet 0

```
+------------------+
| 32 - IV          |
+----ENCRYPTED-----+
| 1  - packet type |
| 1  - flags       |
| 0  - payload     |
+------------------+
```

- Supported flags:
    - End - 0x01:
        - Last packet (only packet)
    - Reliable - 0x02:
        - Ensure the message is delivered correctly and in order
    - Stream: (future) - 0x04
        - Deliver as a stream instead of aggregating the entire message
- Packet type: 0x02

### Packet n

```
+----------------------------------+
| 32  - last 32B ciphertext of msg |
+------------ENCRYPTED-------------+
| 1  - packet type                 |
| 1  - flags                       |
| 1  - padding length (if end)     |
| 0  - payload                     |
| 32 - SHA256 - last packet        |
+----------------------------------+
```

- Supported flags:
    - End:
        - signifies the last packet
- Packet type: 0x03

## Connection Management

### Keepalive + Ping

```
+-----------------+
| 32 - IV         |
+----ENCRYPTED----+
| 1 - packet type |
| 8 - flags       |
| 24 - padding    |
+-----------------+
```

- Packet type: 0x04
- Padding is NULL
- Flags:
    - Ping - 0x01

### Close Connection

```
+-----------------+
| 32 - IV         |
+----ENCRYPTED----+
| 1 - packet type |
| 8 - flags       |
| 24 - padding    |
+-----------------+
```

- Packet type: 0x04
- Padding is NULL
- Flags:
    - Close - 0x02

## Encryption / Security

- RSA-based key exchange
- AES256 symmetric encryption for data
- AES256-CTR used, one CTR per message
- AES256-CBC used in messages
- Messages can randomly (with a probability), nequest a new CTR to blur message boundaries

