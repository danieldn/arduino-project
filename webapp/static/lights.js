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
      } else {
        console.log("return 0");
      }
    });
}

setInterval(get_lights, 1000);
