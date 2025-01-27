class Player {
	
	private var active: Number;
	private var isPlaying: Boolean;
	private var hand: Hand;
	
	public function Player() {
		hand = new Hand(668.8, 175.5);
		reset();
	}
	
	public function reset(): Boolean {
		if (!isPlaying) {
			active = 0;
			isPlaying = true;
			return true;
		} else {
			return false;
		}
	}
	
	public function login(nick: String, pwd: String): Void {
		_root.nick = nick;
		fscommand("Login", nick + "," + pwd);
		_root.dealer.init();
	}
	
	public function getActive(): Number {
		return active;
	}
	
	public function getHand(): Hand {
		return hand;
	}
	
	public function bet(active: Number): Void {
		if (this.active != null) {
			_root.passive -= active;
			this.active += active;
		}
	}
	
	private function fscBet(): Void {
		if (active != null) {
			fscommand("Bet", active.toString());
		}
		active = null;
	}
	
	public function deal(): Void {
		if (active != 0 && hand.isVoid()) {
			fscBet();
			fscommand("Deal", "");
			hand.addCard(_root.dealer.getCard());
			hand.addCard(_root.dealer.getCard());
			hand.turn();
			_root.dealer.deal();
		}
	}
	
	public function double(): Boolean {
		if (hand.length == 2 && isPlaying) {
			fscommand("Double", "");
			hit();
			return true;
		} else {
			return false;
		}
	}
	
	public function hit(): Void {
		if (!hand.isVoid() && hand.getValue()<=21 && isPlaying) {
			fscommand("Hit", "");
			hand.addCard(_root.dealer.getCard());
			hand.turn();
		}
	}
	
	public function stand(): Void {
		if (!hand.isVoid() && isPlaying) {
			fscommand("Stand", "");
			isPlaying = false;
			_root.dealer.stand();
		}
	}
	
	public function store(): Void {
		fscBet();
		fscommand("Save", "");
	}
	
	public function exit(): Void {
		fscBet();
		fscommand("Exit", "");
	}
	
}
