<!DOCTYPE html >

  <head>

      <meta charset="utf-8">

    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <meta name="viewport" content="width=device-width, initial-scale=1">



			<meta charset="utf-8">

		<meta http-equiv="X-UA-Compatible" content="IE=edge">

		<meta name="viewport" content="width=device-width, initial-scale=1">

		<title>PI 2 Senac</title>

		<link href="css/bootstrap.css" rel="stylesheet">

		<link href="css/signin.css" rel="stylesheet">



    <style>



      #map {

        width: 100%;

		height: 600px;

      }

    </style>

  </head>



  <body>

    <!-- Fixed navbar -->

    <nav class="navbar navbar-inverse navbar-fixed-top">

      <div class="container">

        <div class="navbar-header">

          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">

            <span class="sr-only">Navegação</span>

            <span class="icon-bar"></span>

            <span class="icon-bar"></span>

            <span class="icon-bar"></span>

          </button>

          <a class="navbar-brand" href="index.php">PI 2 Senac</a>

        </div>

        <div id="navbar" class="navbar-collapse collapse">

          <ul class="nav navbar-nav">

            <li class="active"><a href="index.php">Home</a></li>

			<li><a href="g_linhas.php">Graficos</a></li>

            <li><a href="administrativo.php">Admin</a></li>

            <li><a href="#contact">Contato</a></li>

	    <li><a href="#about">Sobre</a></li>

          </ul>

        </div><!--/.nav-collapse -->

      </div>

    </nav>

		<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>

		<script src="js/bootstrap.min.js"></script>



    <div id="map"></div><br><br>



    <script>

      var customLabel = {

        restaurant: {

          label: 'R'

        },

        bar: {

          label: 'B'

        }

      };



        function initMap() {

        var map = new google.maps.Map(document.getElementById('map'), {

          center: new google.maps.LatLng(-25.494938, -49.294372),

          zoom: 9

        });

        var infoWindow = new google.maps.InfoWindow;



          // Change this depending on the name of your PHP or XML file

          downloadUrl('resultado.php', function(data) {

            var xml = data.responseXML;

            var markers = xml.documentElement.getElementsByTagName('marker');

            Array.prototype.forEach.call(markers, function(markerElem) {

              var name = markerElem.getAttribute('nome');

              var address = markerElem.getAttribute('endereco');

              var type = markerElem.getAttribute('type');

              var point = new google.maps.LatLng(

                  parseFloat(markerElem.getAttribute('latitude')),

                  parseFloat(markerElem.getAttribute('longitude')));



              var infowincontent = document.createElement('div');

              var strong = document.createElement('strong');

              strong.textContent = name

              infowincontent.appendChild(strong);

              infowincontent.appendChild(document.createElement('br'));



              var text = document.createElement('text');

              text.textContent = address

              infowincontent.appendChild(text);

              var url = 'https://icons.iconarchive.com/icons/icons-land/vista-map-markers/48/';

              var icon = {
                //zoomLevel: 6,
                showTooltip: true,
                showInfoWindow: true,
                //useMapTypeControl: true,
                icons: {
                  blue: {
                    normal:   url + 'Map-Marker-Ball-Azure-icon.png',
                    selected: url + 'Map-Marker-Ball-Right-Azure-icon.png'
                  },
                  green: {
                    normal:   url + 'Map-Marker-Push-Pin-1-Chartreuse-icon.png',
                    selected: url + 'Map-Marker-Push-Pin-1-Right-Chartreuse-icon.png'
                  },
                  pink: {
                    normal:   url + 'Map-Marker-Ball-Pink-icon.png',
                    selected: url + 'Map-Marker-Ball-Right-Pink-icon.png'
                  }
                }
              };

              var marker = new google.maps.Marker({

                map: map,

                position: point,

                label: icon.label

              });

              marker.addListener('click', function() {

                infoWindow.setContent(infowincontent);

                infoWindow.open(map, marker);

              });

            });

          });

        }







      function downloadUrl(url, callback) {

        var request = window.ActiveXObject ?

            new ActiveXObject('Microsoft.XMLHTTP') :

            new XMLHttpRequest;



        request.onreadystatechange = function() {

          if (request.readyState == 4) {

            request.onreadystatechange = doNothing;

            callback(request, request.status);

          }

        };



        request.open('GET', url, true);

        request.send(null);

      }



      function doNothing() {}

    </script>

    <script async defer

    src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCVD_7p837oP7BUFy9zF1u9XX-ch9uNTFA&callback=initMap">





content_copy





    </script>

  </body>

</html>
