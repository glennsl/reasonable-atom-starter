open Rebase;

let toggle panel => {
  Js.log "reasonable-atom-starter was toggled!";
  Atom.Panel.(isVisible panel ? hide panel : show panel);
};

include Atom.Hooks {
  type state = {
    modalPanel: Atom.panel,
    subscriptions: Atom.compositeDisposable,
    view: View.t
  };

  type serializedState = Js.t {.
    viewState: View.state
  };

  let activate serializedState => {
    Js.log "activate";
    let view = View.make (Option.map (fun s => s##viewState) serializedState);
    let modalPanel = Atom.Workspace.addModalPanel {
      "item": View.getElement view,
      "visible": Js.false_
    };

    let subscriptions = Atom.CompositeDisposable.make ();

    Atom.CompositeDisposable.add subscriptions
      (Atom.Commands.add "atom-workspace" {
        "reasonable-atom-starter:toggle": fun () => toggle modalPanel
      });

    { view, modalPanel, subscriptions }
  };

  let deactivate state => {
    Js.log "deactivate";
    Atom.Panel.destroy state.modalPanel;
    Atom.CompositeDisposable.destroy state.subscriptions;
    View.destroy state.view;
  };

  let serialize state => {
    Js.log "serialize";
    { "viewState": View.serialize state.view }
  };
};
