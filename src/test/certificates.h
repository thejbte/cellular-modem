/*
 * certificates.h
 *
 *  Created on: Oct 4, 2021
 *      Author: julian
 */

#ifndef INC_APPCODE_CERTIFICATES_H_
#define INC_APPCODE_CERTIFICATES_H_

//https://serverfault.com/questions/466683/can-an-ssl-certificate-be-on-a-single-line-in-a-file-no-line-breaks

#define CA_CERT					"-----BEGIN CERTIFICATE-----\n\
MIID4zCCAsugAwIBAgIJANRAEQOx5XgHMA0GCSqGSIb3DQEBBQUAMIGHMQswCQYD\n\
VQQGEwJDTjELMAkGA1UECAwCQUgxCzAJBgNVBAcMAkhGMRAwDgYDVQQKDAdRVUVD\n\
VEVMMQswCQYDVQQLDAJTVDEYMBYGA1UEAwwPMjIwLjE4MC4yMzkuMjEyMSUwIwYJ\n\
KoZIhvcNAQkBFhZkYWlzeS50aWFuQHF1ZWN0ZWwuY29tMB4XDTE4MTIyOTA5MjA0\n\
OVoXDTE5MTIyOTA5MjA0OVowgYcxCzAJBgNVBAYTAkNOMQswCQYDVQQIDAJBSDEL\n\
MAkGA1UEBwwCSEYxEDAOBgNVBAoMB1FVRUNURUwxCzAJBgNVBAsMAlNUMRgwFgYD\n\
VQQDDA8yMjAuMTgwLjIzOS4yMTIxJTAjBgkqhkiG9w0BCQEWFmRhaXN5LnRpYW5A\n\
cXVlY3RlbC5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCrJqRp\n\
UY20js0xXzqRxau6y6pf/U+0xlMiig8nxQ2XRTksEpV03roTSzNjamSvJFCL+juK\n\
Yt8ADg745qCFv4+mFbpit9/93veWTqHT7BpiPLJBGy7UFs5ZIg9M5Bf68xUvPFn4\n\
aANU6WsUYGDyBAeivY4qX1xFPgS7wk416ahzyVuWbWF/d7lT+PW7fdOa1UkbBBXo\n\
uwf9NiEho3c0X5BnORcplYhQTqciIhO8owlzdXbzC80ddGbJz13tpxVE2vaQyqdP\n\
7OENK9lnhhnZcYDsrE+kcYceqoLbSgAHOXav6YXvAnYV957KIMGMAgRUQzNp32Uq\n\
1EPX/+9YCObi+ydfAgMBAAGjUDBOMB0GA1UdDgQWBBRrIEEfh1dcwa0kvEDJTNs1\n\
le6qYDAfBgNVHSMEGDAWgBRrIEEfh1dcwa0kvEDJTNs1le6qYDAMBgNVHRMEBTAD\n\
AQH/MA0GCSqGSIb3DQEBBQUAA4IBAQBV8fnk05IZkCo1yIafs8HkyfedXgRUjjcY\n\
NZJaw0B+Q1iGizBfG2cmwuIV08olMzc6V4qe6L8nRUyNJnk6ZLVPLarzneG5vI5d\n\
F5y0wwLmg5YZw6/n8wFHsbB+OYUDFgTWp8JeqNCviW6ixg0G/YmMjQzbymWUVjCV\n\
5adP+9uMxE6kgAUO5Fa6XMfhFf+ofmF69T4Zh7Te0fCXTcYsS2pv++bbgP1yxON5\n\
1SfLi+eaUMvrpz5NR+P143A5mJKEMsyWnQSNzWnJnSpdCnwZluoE9YheKD27Ov3n\n\
7RwPk9UWUgUOQtC0TQYaru+3v61zU+isE06yXOMT3eR/OtIFUZqK\n\
-----END CERTIFICATE-----\n"

#define USER_CLIENT_CERT 			"-----BEGIN CERTIFICATE-----\n\
MIID+DCCAuCgAwIBAgIBATANBgkqhkiG9w0BAQUFADCBhzELMAkGA1UEBhMCQ04x\n\
CzAJBgNVBAgMAkFIMQswCQYDVQQHDAJIRjEQMA4GA1UECgwHUVVFQ1RFTDELMAkG\n\
A1UECwwCU1QxGDAWBgNVBAMMDzIyMC4xODAuMjM5LjIxMjElMCMGCSqGSIb3DQEJ\n\
ARYWZGFpc3kudGlhbkBxdWVjdGVsLmNvbTAeFw0xODEyMjkwOTI3MzlaFw0xOTEy\n\
MjkwOTI3MzlaMHoxCzAJBgNVBAYTAkNOMQswCQYDVQQIDAJBSDEQMA4GA1UECgwH\n\
UVVFQ1RFTDELMAkGA1UECwwCU1QxGDAWBgNVBAMMDzIyMC4xODAuMjM5LjIxMjEl\n\
MCMGCSqGSIb3DQEJARYWZGFpc3kudGlhbkBxdWVjdGVsLmNvbTCCASIwDQYJKoZI\n\
hvcNAQEBBQADggEPADCCAQoCggEBANbCEjGNCtiDhU551efjIRrecleXV8Vgq8X9\n\
zJ6mRwwPczTZESuXBUdxxhDYi4YSkU4QdSicckHxo1buRMpBGDMZzy2XLA4HWW5D\n\
0Q9hf8Cy8eyhXSeWGIT2tA3T6uLRj7SbKsyHkW2ddJwgPwpOEuvlevS1pGDdITwL\n\
bQgqM39zMaquHCoUqsRFGwwoEKeAi6+Pq54l3MNdVnC8/evoTjJyzJDI7DxZJVUb\n\
K0OSWY9iHejGI5Bse6/bQYiah6VUq5zUtvO8FjEHeJDePxO9pWXNkJbzlu+ABKjs\n\
X/ft8FEQND/G0oGPmeJM3l/BJExOaSWssM7nEXl9KNaVXIRheVUCAwEAAaN7MHkw\n\
CQYDVR0TBAIwADAsBglghkgBhvhCAQ0EHxYdT3BlblNTTCBHZW5lcmF0ZWQgQ2Vy\n\
dGlmaWNhdGUwHQYDVR0OBBYEFH9eBPF9NR+QTaK5EnkhtEOd143sMB8GA1UdIwQY\n\
MBaAFGsgQR+HV1zBrSS8QMlM2zWV7qpgMA0GCSqGSIb3DQEBBQUAA4IBAQBVQTR3\n\
YxQBrvZvIHBWIVLIYTIqPeuAAa6k1uuzvPMFwY0akW2mzYn1STtt99SrI2Pgk2dD\n\
Ac9cUTLJP/8padaBY+xPpUmjJa3kQUuzM+2L9btBOkTCtdaMbacjNuITCOQ6N24v\n\
ZR0zDdgwD7sc08MZUsmHT0bA5alE00oOR0b8gfS7dTd1DRbhQv0ZH7uz4mTztbar\n\
RjjFaJI0f5TE08xrQAKiB3tOynyhMQL3jhLkFea2AEMp3Rq1ZoLOr9/ANL0nA10f\n\
pkhvgyrGde7ftNSfcMfQ621MjP++BgUMdTstnjXTNV+xK0vHQPWyxPJ6lEFIcfaR\n\
weP35u+LV1kAFm35\n\
-----END CERTIFICATE-----\n"

#define USER_KEY_CERT 			"-----BEGIN PRIVATE KEY-----\n\
MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDWwhIxjQrYg4VO\n\
edXn4yEa3nJXl1fFYKvF/cyepkcMD3M02RErlwVHccYQ2IuGEpFOEHUonHJB8aNW\n\
7kTKQRgzGc8tlywOB1luQ9EPYX/AsvHsoV0nlhiE9rQN0+ri0Y+0myrMh5FtnXSc\n\
ID8KThLr5Xr0taRg3SE8C20IKjN/czGqrhwqFKrERRsMKBCngIuvj6ueJdzDXVZw\n\
vP3r6E4ycsyQyOw8WSVVGytDklmPYh3oxiOQbHuv20GImoelVKuc1LbzvBYxB3iQ\n\
3j8TvaVlzZCW85bvgASo7F/37fBREDQ/xtKBj5niTN5fwSRMTmklrLDO5xF5fSjW\n\
lVyEYXlVAgMBAAECggEAZuyR7Z+MECJQVED97GmlZwwvPp1w2k6vZG9zjqFgMX6C\n\
F1Tk7sAtLoVviIlPrQzfCMvIapM4CzS0tKfy3f/+ihcXfOEToxGQodDss/NlV8Qr\n\
P95CGAPOcoMN3gavbs9CkStAgs+COkeZKG4n6FdsqBPOLtOTGT1BfVZ4hc476hs5\n\
dY6QgZlkQgKttYfR1dOzdKYLVE/hWKxEx/14Ee4azhMxPqQZkTfSt+AijJY81q+B\n\
cTOpL823hxLn06Gy5RBZqpX4Yc9GBtwHiVJZ0TOhl+hjTJJjY4KlFCt02G3CsHNX\n\
c+/dPagGTynkI7e3x6oVoHkN9QUmKR388cErKDR3AQKBgQDqhXeaBynkWYpyiZAp\n\
IxgcpR8v1cFNITE8VLLFabtvDUjYkqePlstQCA4915NJEfxOTP32GJ1SluIQ3zFt\n\
wWrEhUW3WLrYNxtW2t1X2qOFb/xUXTkeDLxfxAryaIuPXriab292FELsGSRSQKr3\n\
NVUBlzyhCd1+059Zl53yO6kmwQKBgQDqbT0synXQ7YVt7jmXcwS78kLGiVrbSD4R\n\
+SMnGICSVUbHZwqH01tZboJ2d5aQILUCNZsmolK7WjTrAMFoaAHgKAzRhjDyz5zO\n\
uCoSBm9Ig0tcceNbB/7ehRMrp+Vp71nHHs/dfIGZu+M/wyZZ0yvL/72ox2qepscw\n\
+ycz08urlQKBgF0/WEDMHGIJID1OaR2SMKIjHXVdnpBWZEdCvho0YixTseU62pkD\n\
Mi/OJCt+rbdeCV3wywGw48zU5Woj9HlZcGRXQVMXWqNhteMg/uVRr7b8we2ha3aB\n\
Rd0mC9w6qVMGLIxrRnxCriFGFeUGhXPpprUNNzQowgMNjcyHtmt8QVOBAoGBAKHi\n\
h/FLaqq5q3+rl/e/BNDpTjWeGrD9JWfx/NV9tSPYYcVHod0EFrwedVdr4/xpqbX5\n\
4MeAJtOcSpjSb70yvcDWx2tVWK4EssuKH/tMmEKh8EPJnfB6CAYQLZnjGqjaEcxQ\n\
ucjAtxq7xgV9NRmom0EHvSg1dapTj5CCj6LZqnc1AoGAPZJJz3UFIHQwK/GMMZLo\n\
ru08Lqup0DBOQ1tbBxABVx7UrCeUoUBZCNcXWM0SKGKltJk/jvFGMlbGJHWe0uKF\n\
uZrMNqtE4DcwNLjpdlf1wuQNLpSGqNFKIS5eu3y2E8ree3pX4S6vyL3zhLjkrbrE\n\
5BzLe8bKqNEEB+pxsYBQhuU=\n\
-----END PRIVATE KEY-----\n"

/*	qDebug_Message(CA_CERT);
	qDebug_Decimal(strlen(CA_CERT));
	qDebug_Message(USER_CERT);
	qDebug_Decimal(strlen(USER_CERT));
	qDebug_Message(KEY_CERT);
	qDebug_Decimal(strlen(KEY_CERT));
	*/
#endif /* INC_APPCODE_CERTIFICATES_H_ */
