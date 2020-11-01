# Node-Resizer

## Sample Image
![Screenshot](images/lgtm.jpg)

## Sample base64
[click me please](images/lgtm.b64)

## Build and take a shower
``` bash
$ docker build -t resizer:latest .
```
## Run
``` bash
$ docker run -it --rm --network host --name resizer resizer:latest resizer
```

## Usage
Endpoint
```
POST http://localhost:8080/resize_image
```

Header
```
Content-Type: application/json
```

Request Body JSON
```
{
    "input_jpeg": "<open-images/lgtm.b64>",
    "desired_width": 1080,
    "desired_height": 720
}
```

Response Body JSON
```
{
    "code": 200,
    "message": "success",
    "output_jpeg": <output>
}
```

## Notes
Don't forget to check the results on this website
- https://codebeautify.org/base64-to-image-converter
