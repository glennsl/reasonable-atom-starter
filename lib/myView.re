open ReasonJs;
open ReasonJs.Dom;

type state;

type t = {
  element: element
};

let make : state => t = fun _ => {
  let element = document |> Document.createElement "div";
  Element.setClassName element "view";

  let message = document |> Document.createElement "div";
  Element.setTextContent message "The atom-reason-starter package is Alive! It's ALIVE!";
  Element.setClassName message "view";
  Element.appendChild (message |> Element.asNode) element;

  { element: element }
};

let getElement : t => element = fun self => self.element;
let serialize : t => Js.t {..} = fun _ => [%bs.raw "{}"];
let destroy : t => unit = fun self => Element.remove self.element;
