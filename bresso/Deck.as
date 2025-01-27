class Deck extends MovieClip {
	
	private var me: Array;
	private var top: Card;
	
	public function Deck() {
		super();
		me = new Array(52);
		me[0] = top;
		var i:Number;
		for (i=1; i<52; i++) {
			me[i] = me[i-1].duplicateMovieClip("card"+i.toString(), i);
			me[i]._x += .2;
			me[i]._y += .1;
		}
	}
	
	public function init(): Void {
		var aDeck: Array = _root.sDeck.split(",");
		me[0].init(aDeck[0]);
		var i:Number;
		for (i=1; i<52; i++) {
			me[i].init(aDeck[i]);
		}
	}
	
	public function reset(): Void {
		me[me.length-1].gotoAndStop(1);
		var card: Card;
		var i: Number;
		var j: Number = _root.player.getHand().length - 2;
		for (i=0; i<j; i++) {
			card = _root.player.getHand().pop();
			card.reset();
			me[me.length] = card;
		}
		j = _parent.getHand().length;
		for (i=0; i<j; i++) {
			card = _parent.getHand().pop();
			card.reset();
			me[me.length] = card;
		}
		j = _root.player.getHand().length;
		for (i=0; i<j; i++) {
			card = _root.player.getHand().pop();
			card.reset();
			me[me.length] = card;
		}
	}
	
	public function popCard(): Object {
		return me.pop();
	}
	
	public function turn(): Void {
		me[me.length-1].gotoAndStop(2);
	}
	
}
