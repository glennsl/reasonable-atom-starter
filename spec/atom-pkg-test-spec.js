'use babel';

import AtomPkgTest from '../lib/atom-pkg-test';

// Use the command `window:run-package-specs` (cmd-alt-ctrl-p) to run specs.
//
// To run a specific `it` or `describe` block add an `f` to the front (e.g. `fit`
// or `fdescribe`). Remove the `f` to unfocus the block.

describe('AtomPkgTest', () => {
  let workspaceElement, activationPromise;

  beforeEach(() => {
    workspaceElement = atom.views.getView(atom.workspace);
    activationPromise = atom.packages.activatePackage('atom-pkg-test');
  });

  describe('when the atom-pkg-test:toggle event is triggered', () => {
    it('hides and shows the modal panel', () => {
      // Before the activation event the view is not on the DOM, and no panel
      // has been created
      expect(workspaceElement.querySelector('.atom-pkg-test')).not.toExist();

      // This is an activation event, triggering it will cause the package to be
      // activated.
      atom.commands.dispatch(workspaceElement, 'atom-pkg-test:toggle');

      waitsForPromise(() => {
        return activationPromise;
      });

      runs(() => {
        expect(workspaceElement.querySelector('.atom-pkg-test')).toExist();

        let atomPkgTestElement = workspaceElement.querySelector('.atom-pkg-test');
        expect(atomPkgTestElement).toExist();

        let atomPkgTestPanel = atom.workspace.panelForItem(atomPkgTestElement);
        expect(atomPkgTestPanel.isVisible()).toBe(true);
        atom.commands.dispatch(workspaceElement, 'atom-pkg-test:toggle');
        expect(atomPkgTestPanel.isVisible()).toBe(false);
      });
    });

    it('hides and shows the view', () => {
      // This test shows you an integration test testing at the view level.

      // Attaching the workspaceElement to the DOM is required to allow the
      // `toBeVisible()` matchers to work. Anything testing visibility or focus
      // requires that the workspaceElement is on the DOM. Tests that attach the
      // workspaceElement to the DOM are generally slower than those off DOM.
      jasmine.attachToDOM(workspaceElement);

      expect(workspaceElement.querySelector('.atom-pkg-test')).not.toExist();

      // This is an activation event, triggering it causes the package to be
      // activated.
      atom.commands.dispatch(workspaceElement, 'atom-pkg-test:toggle');

      waitsForPromise(() => {
        return activationPromise;
      });

      runs(() => {
        // Now we can test for view visibility
        let atomPkgTestElement = workspaceElement.querySelector('.atom-pkg-test');
        expect(atomPkgTestElement).toBeVisible();
        atom.commands.dispatch(workspaceElement, 'atom-pkg-test:toggle');
        expect(atomPkgTestElement).not.toBeVisible();
      });
    });
  });
});
