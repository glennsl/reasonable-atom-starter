
module Atom = {
  type compositeDisposable;
  type disposable;
  type panel;

  module CompositeDisposable = {
    type t = compositeDisposable;

    external make : unit => t = "CompositeDisposable" [@@bs.new] [@@bs.module "atom"];

    external add : t => disposable => unit = "" [@@bs.send];
    external destroy : t => unit = "" [@@bs.send];
  };

  module Commands = {
    external add : string => Js.t {..} => disposable = "atom.commands.add" [@@bs.val];
  };

  module Panel = {
    type t = panel;

    external isVisible : t => Js.boolean = "" [@@bs.send];
    external hide : t => unit = "" [@@bs.send];
    external show : t => unit = "" [@@bs.send];
    external destroy : t => unit = "" [@@bs.send];
  };

  module Workspace = {
    external addModalPanel : Js.t {..} => panel = "atom.workspace.addModalPanel" [@@bs.val];
  };

};

type state;

module MyView = {
  open ReasonJs;
  open ReasonJs.Dom;

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
};

type self = {
  mutable modalPanel: Js.undefined Atom.panel,
  mutable subscriptions: Js.undefined Atom.compositeDisposable,
  mutable view: Js.undefined MyView.t
};

let toggle self => {
  Js.log "atom-reason-starter was toggled!";
  Js.Undefined.iter self.modalPanel
    ((fun panel => Atom.Panel.(Js.to_bool (isVisible panel) ? hide panel : show panel)) [@bs]);
};

let activate = (fun self state => {
  self.view = Js.Undefined.return (MyView.make state);
  self.modalPanel = Js.Undefined.return (Atom.Workspace.addModalPanel {
    "item": Js.Undefined.bind self.view ((fun e => MyView.getElement e) [@bs]),
    "visible": Js.false_
  });

  let subscriptions = Atom.CompositeDisposable.make ();
  self.subscriptions = Js.Undefined.return subscriptions;

  Atom.CompositeDisposable.add subscriptions
    (Atom.Commands.add "atom-workspace" {
      "atom-reason-starter:toggle": fun () => toggle self
    });
}) [@bs.this];

let deactiveate = (fun self => {
  Js.Undefined.iter self.modalPanel ((fun panel => Atom.Panel.destroy panel) [@bs]);
  Js.Undefined.iter self.subscriptions ((fun subs => Atom.CompositeDisposable.destroy subs) [@bs]);
  Js.Undefined.iter self.view ((fun view => MyView.destroy view) [@bs]);
}) [@bs.this];

let serialize = (fun self => Js.Undefined.bind self.view ((fun view => {
  "viewState": MyView.serialize view
}) [@bs])) [@bs.this];
