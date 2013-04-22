/**
 * 
 * This script is developed for research purposes only,
 * recall that the site rules of yourturnmyturn.com "consider unsporting to use a computer to determine your move"
 * and says that "every form of cheating where you win a board game not on your own is forbidden".
 *
 */


var casper = require("casper").create(
	{
		logLevel: "debug",
		verbose : true,
		clientScripts:  [],
		onError: function(self, m) {   // Any "error" level message will be written
			console.log('FATAL:' + m); // on the console output and PhantomJS will
			self.exit();               // terminate
		},
		pageSettings: {
		    loadImages:  true,        // The WebPage instance used by Casper will
		    loadPlugins: false,         // use these settings
		    javascriptEnabled: true
		},
	    stepTimeout : 600*1000
	}
);

var username;
var password;

loginURL = 'http://www.yourturnmyturn.com/';
gameURL = 'http://www.yourturnmyturn.com/reversi/play.php?gamenumber=';

var row;
var column;

if (casper.cli.has(0) && casper.cli.has(1) && casper.cli.has(2) && casper.cli.has(3) && casper.cli.has(4)) {
	// if (casper.cli.has(0) && casper.cli.has(1) && casper.cli.has(2)) {
	username = casper.cli.get(0);
	password = casper.cli.get(1);
	gameURL += casper.cli.get(2);
	row = casper.cli.get(3);
	column = casper.cli.get(4);
} else {
	casper.echo("usage: casperjs makeMove.js <username> <password> <gamenumber> <row> <column>");
	casper.exit();
}

casper.start(loginURL, function() {
	
	console.log("START");
	
	this.fill('form[name="myform"]', { username_form: username, password_form : password }, true);
	
});

casper.thenOpen(gameURL,function() {

	console.log("I'm making the move");

	var currentURL = this.getCurrentUrl();
	
	this.echo(currentURL);

	var patt=/show/;
	
	if(patt.test(currentURL))
		console.log("It's not my turn!");
	else {

		var id = 'bord' + ((row - 1) * 8 + (column - 1));

		console.log("id: " + id);

		this.test.assertExists('#' + id, 'the element exists');

		this.click('#' + id );

		this.click('#OKknop');
		
	}

	console.log("END");

});


casper.run(function() {
    this.exit();
});
