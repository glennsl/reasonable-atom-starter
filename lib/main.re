open Rebase;

let toggle panel => {
  Js.log "atom-reason-starter was toggled!";
  Atom.Panel.(isVisible panel ? hide panel : show panel);
};

include Atom.Hooks {
  type state = {
    modalPanel: Atom.panel,
    subscriptions: Atom.compositeDisposable,
    view: MyView.t
  };

  type serializedState = Js.t {.
    viewState: MyView.state
  };

  let activate serializedState => {
    Js.log "activate";
    let view = MyView.make (Option.map (fun s => s##viewState) serializedState);
    let modalPanel = Atom.Workspace.addModalPanel {
      "item": MyView.getElement view,
      "visible": Js.false_
    };

    let subscriptions = Atom.CompositeDisposable.make ();

    Atom.CompositeDisposable.add subscriptions
      (Atom.Commands.add "atom-workspace" {
        "atom-reason-starter:toggle": fun () => toggle modalPanel
      });

    { view, modalPanel, subscriptions }
  };

  let deactivate state => {
    Js.log "deactivate";
    Atom.Panel.destroy state.modalPanel;
    Atom.CompositeDisposable.destroy state.subscriptions;
    MyView.destroy state.view;
  };

  let serialize state => {
    Js.log "serialize";
    { "viewState": MyView.serialize state.view }
  };
};
