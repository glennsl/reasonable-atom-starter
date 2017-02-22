
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
