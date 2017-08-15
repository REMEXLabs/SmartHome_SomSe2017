# Health Hub Backend
Node.js application providing an interface to communicate with the HealthHub system

## Table of Contents

- Prerequisites
- Installation
  - Frontend Installation
- Execution
  - Webserver
  - Database
  - Frontend
- API  

## Prerequisites

- Required:
  - NodeJS, version 6.11.1+
  - Node Package Manager, version 5.3.0+
  - MongoDb, version 3.4.6+

- Optional:
  - Nodemon, restarts nodejs-server if any file changes in the source code are made


## Installation

After you fulfilled all the prerequisites you need to install the required packages.
From the root-directory run

```sh
npm install
```
The installed packages are stored in the *node_modules* folder.

### Frontend Installation
```
cd angular-src
npm install
```
***NOTE:*** The code for the Angular2 Frontend is in `angular-src`-Folder. Build-output will be copied to `public`-Folder.

## Execution

### Webserver
Call `node server.js` in the root-folder to start the webserver

### Database
Start the mongodb-server in the your mongodb installation folder, e.g. `cd /usr/local/opt/mongodb/; mongod`

### Frontend
start the Angular2 Frontend with `cd /angular-src/; ng serve`.

Build the frontend with:
```
cd angular-src
ng build
```

As already mentioned above the build-output is stored in the *public* folder.

## API
**Port 9080 (websocket)**

**Events**

 a) Received by backend
- connection
- New-User

b) Emitted by backend

The backend emits messages with different message-types and data-types, listed below
- message
    - *Registration*
      - type: setup-started
      - type: setup-scan-1
      - type: setup-scan-2
      - type: setup-scan-3
      - type: setup-success
    - *Start Scan*
      - type: scan-started
    - *During Scan*
      - type: user-identified, data: JSON
      ```javascript
      // example response
      {
        "id": "1",
        "lastname": "Mustermann",  
        "firstname": "Max",  
        "technicalAffinity": "low",  
        "thirdPartyAccess": "false"
      }
      ```
      - type: sensor-finished, data: JSON
      ```javascript
      // example response
      {
        "value": "100",
        "text": "normal"
      }
      ```
      - type: pulse-stream, value: String
      - type: scan-finished
      - type: scan-failed

**Port 3000 (HTTP)**

* /getData

GET http://localhost:3000/getData

```javascript
// example response
{
    "surename": "Mustermann",
     "name": "Max",  
     "heartrate": "100",  
     "temp": "38",  
     "gsr": "8",
     "stress": "high"
}
```

* /setup

POST http://localhost:3000/setup

```javascript
// example request
{
    "message": "setup"
}
```
