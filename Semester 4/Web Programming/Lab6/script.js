$(document).ready(function() {
    var score = 0;

    function placeImage() {
      var windowHeight = $(window).height() - 100; 
      var windowWidth = $(window).width() - 100; 
      var posY = Math.floor(Math.random() * windowHeight);
      var posX = Math.floor(Math.random() * windowWidth);
      var img = $('<img src="danDiaconescu.jpg">');

      img.css({
        top: posY + 'px',
        left: posX + 'px'
      });

      img.on('click', function() {
        score++;
        $('#score').text('Score: ' + score);
        $(this).remove(); 

        if (score >= 10) {
          alert('Congratulations! You won!');
          location.reload(); 
        }
      });

      $('body').append(img);

      
      setTimeout(function() {
        img.remove();
      }, Math.random() * 2000 + 1000); 
    }

    function startGame() {
      setInterval(placeImage, 2000); 
    }

    startGame();
  });