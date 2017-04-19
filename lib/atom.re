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
  let isVisible : t => bool = fun self => Js.to_bool (isVisible self);
  external hide : t => unit = "" [@@bs.send];
  external show : t => unit = "" [@@bs.send];
  external destroy : t => unit = "" [@@bs.send];
};

module Workspace = {
  external addModalPanel : Js.t {..} => panel = "atom.workspace.addModalPanel" [@@bs.val];
};

module type HooksSpec = {
  type state;
  type serializedState;

  let activate : option serializedState => state;
  let serialize : state => serializedState;
  let deactivate : state => unit;
};

module Hooks (Spec: HooksSpec) => {
  type self = {
    mutable state: Spec.state
  };

  let activate = (fun self serializedState => {
    self.state = Spec.activate (Js.Undefined.to_opt serializedState);
  }) [@bs.this];

  let serialize = (fun self => Spec.serialize self.state) [@bs.this];

  let deactivate = (fun self => Spec.deactivate self.state) [@bs.this];
};
