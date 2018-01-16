type appItem = {
  id: int,
  title: string,
  completed: bool
};

type appState = {items: list(appItem)};

type appAction =
  | AddItem(string)
  | ToggleItem(int);

let lastId = ref(0);

let newItem = title => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: false};
};

let appReducer = (action, {items}) =>
  switch action {
  | AddItem(title) => ReasonReact.Update({items: [newItem(title), ...items]})
  | ToggleItem(id) =>
    let items =
      List.map(
        item => item.id === id ? {...item, completed: ! item.completed} : item,
        items
      );
    ReasonReact.Update({items: items});
  };