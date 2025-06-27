<input id="thresholdInput" type="number" placeholder="Set threshold °C">
<button onclick="setThreshold()">Set</button>
<p id="currentTemp">Temp: -- °C</p>

<script>
function setThreshold() {
  let val = document.getElementById("thresholdInput").value;
  fetch("/set?value=" + val)
    .then(res => res.text())
    .then(data => alert(data));
}

setInterval(() => {
  fetch("/temp")
    .then(res => res.text())
    .then(temp => {
      document.getElementById("currentTemp").innerText = "Temp: " + temp + " °C";
    });
}, 2000);
</script>
