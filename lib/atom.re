
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
