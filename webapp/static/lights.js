"use strict";

// Sending requests to Flask to turn the motion sensor on or off
$( document ).ready(function() {
  $('.checkbox').change(function() {
      if($(this).is(':checked')) {
        $.ajax({
          type: "GET",
          url: "/on",
          async: false
        });
      } else {
        $.ajax({
          type: "GET",
          url: "/off",
          async: false
        });
      }
  });
});

// Grabbing the current state every second and changing the colors on the website accordingly
function get_lights(){
    var feedback = $.ajax({
        type: "GET",
        url: "/lights",
        async: false
    }).done(function(data){
      if (data === "1") {
        // console.log("return 1");
        $('#bulb').addClass('bulb-on').removeClass('bulb-off');
        $('body').addClass('light');
      } else {
        // console.log("return 0");
        $('#bulb').removeClass('bulb-on').addClass('bulb-off');
        $('body').removeClass('light');
      }
    });
}

setInterval(get_lights, 1000);
