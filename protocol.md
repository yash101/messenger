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
| 1  - packet type |
| 32 - IV          |
+----ENCRYPTED-----+
| 1  - flags       |
| 0  - payload     |
+------------------+
```

- Supported flags:
    - Reliable:
        - Ensure the message is delivered correctly and in order
    - End:
        - Last packet (only packet)
- Packet type: 0x02

### Packet n

```
+---------------------------------+
| 1  - packet type                |
| 32 - last 32B ciphertext of msg |
+-----------ENCRYPTED-------------+
| 1 - flags                       |
| 1 - padding length (if end)     |
| 0 - payload                     |
+---------------------------------+
```

- Supported flags:
    - End:
        - signifies the last packet
- Packet type: 0x03

## Connection Management

### Keepalive + Ping

```
+-----------------+
| 1 - packet type |
| 0 - payload     |
+----ENCRYPTED----+
| 8 - flags       |
| 24 - padding    |
+-----------------+
```

- Payload gets reflected back to the sender
- Padding is NULL

### Close Connection

```
+-----------------+
| 1 - packet type |
| 32 - IV         |
+----ENCRYPTED----+
| 8 - flags       |
| 24 - padding    |
+-----------------+
```

- Padding is NULL
