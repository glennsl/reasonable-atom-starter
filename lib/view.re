type state = unit;

type t = {
  element: Dom.element
};

let make : option state => t = fun _ => {
  open ReasonJs.Dom;
  
  let element = document |> Document.createElement "div";
  Element.setClassName element "view";

  let message = document |> Document.createElement "div";
  Element.setTextContent message "The reasonable-atom-starter package is Alive! It's ALIVE!";
  Element.setClassName message "reasonable-atom-starter";
  Element.appendChild message element;

  { element: element }
};

let getElement : t => Dom.element = fun self => self.element;
let serialize : t => state = fun _ => ();
let destroy : t => unit = fun self => ReasonJs.Dom.Element.remove self.element;
