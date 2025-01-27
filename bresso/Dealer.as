class Dealer extends MovieClip {
	
	private var deck: Deck;
	private var hand: Hand;
	
	public function Dealer() {
		super();
		onEnterFrame = update;
		hand = new Hand(0, 175.5);
	}
	
	public function init(): Void {
		deck.init();
	}
	
	public function reset(): Void {
		deck.reset();
		init();
	}
	
	public function getHand(): Hand {
		return hand;
	}
	
	public function getCard(): Object {
		return deck.popCard();
	}
	
	private function hit() {
		hand.addCard(getCard());
	}
	
	public function deal(): Void {
		hit();
		hit();
		hand.turnTop();
	}
	
	public function stand(): Void {
		hand.turn();
		deck.turn();
	}
	
	private function update(): Void {/*
		if (!(_root.sDeck eq "")) {
			deck.init();
			_root.sDeck = "";
		}*/
		if (!(_root.hits eq "0")) {
			var hits: Number = new Number(_root.hits);
			while (hits != 0) {
				hit();
				hits--;
			}
			_root.hits = "0";
		}
		if (!(_root.msg eq "")) {
			_root.alert(_root.msg, 340, 100);
			_root.msg = "";
		}
	}
	
}
