type item = {
  id: int,
  title: string,
  completed: bool
};

type state = {items: list(item)};

type action =
  | AddItem(string)
  | ToggleItem(int);

let lastId = ref(0);

let newItem = title => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: false};
};

let reducer = (action, {items}) =>
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