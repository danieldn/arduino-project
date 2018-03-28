"use strict";

function get_lights(){
  console.log("working");
    var feedback = $.ajax({
        type: "GET",
        url: "/lights",
        async: false
    }).done(function(data){
      if (data === "1") {
        console.log("return 1");
        $('#bulb').addClass('bulb-on').removeClass('bulb-off');
        $('body').addClass('light');
      } else {
        console.log("return 0");
        $('#bulb').removeClass('bulb-on').addClass('bulb-off');
        $('body').removeClass('light');
      }
    });
}

setInterval(get_lights, 1000);
