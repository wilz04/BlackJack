class Hand extends Array {
	
	private var width: Number;
	private var height: Number;
	private var x:Number;
	private var y:Number;
	
	public function Hand(x:Number, y:Number) {
		super();
		width = 119.8;
		height = 145.3;
		this.x = x;
		this.y = y;
	}
	
	public function getValue(): Number {
		var val: Number = 0;
		var i: Number;
		for (i=0; i<length; i++) {
			val += this[i].getValue();
		}
		return val;
	}
	
	public function addCard(card: Object): Void {
		var spacer: Number = width/(length==0?1:length);
		var i: Number;
		for (i=0; i<length; i++) {
			this[i]._x = x + spacer*i*(x==0?1:-1);
		}
		card._x = x + spacer*length*(x==0?1:-1);
		card._y = y;
		push(card);
	}
	
	public function isVoid(): Boolean {
		return this[0] == undefined;
	}
	
	public function turnTop(): Void {
		this[0].gotoAndStop(2);
	}
	
	public function turn(): Void {
		var i: Number;
		for (i=0; i<length; i++) {
			this[i].gotoAndStop(2);
		}
	}
	
}
