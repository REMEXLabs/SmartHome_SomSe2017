import { RemactUiPage } from './app.po';

describe('remact-ui App', () => {
  let page: RemactUiPage;

  beforeEach(() => {
    page = new RemactUiPage();
  });

  it('should display message saying app works', () => {
    page.navigateTo();
    expect(page.getParagraphText()).toEqual('app works!');
  });
});
