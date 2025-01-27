class Card extends MovieClip {
	
	private var _caption: String;
	private var _type: String;
	private var x: Number;
	private var y: Number;
	
	public function Card() {
		super();
		_caption = "A";
		_type = "Oros";
		x = 0;
		y = 0;
	}
	
	public function init(sCard: String): Void {
		var aCard:Array = sCard.split("-");
		_caption = aCard[0];
		_type = aCard[1];
		x = _x;
		y = _y;
	}
	
	public function reset(): Void {
		gotoAndStop(1);
		_x = x;
		_y = y;
	}
	
	private function getValue(): Number {
		var captions: Array = new Array("A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K");
		var i: Number;
		for (i=0; i<12; i++) {
			if (captions[i] eq _caption) {
				break;
			}
		}
		return ++i;
	}
	
}
