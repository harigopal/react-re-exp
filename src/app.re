type todoItem = {
  id: int,
  title: string,
  completed: bool
};

let str = ReasonReact.stringToElement;

type appAction =
  | AddItem(string)
  | ToggleItem(int);

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~appReduce, _children) => {
    ...component,
    render: _self =>
      <div onClick=(appReduce(_event => ToggleItem(item.id)))>
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
        />
        (str(item.title))
      </div>
  };
};

let valueFromInputEvent = event : string => (
                                              event
                                              |> ReactEventRe.Form.target
                                              |> ReactDOMRe.domElementToObj
                                            )##value;

type todoFormState = {title: string};

module TodoForm = {
  let component = ReasonReact.reducerComponent("TodoForm");
  let make = (~appReduce, _children) => {
    ...component,
    initialState: () => {title: ""},
    reducer: (title, _state) => ReasonReact.Update({title: title}),
    render: ({state: {title}, reduce}) =>
      <form
        onSubmit=(
          event => {
            ReactEventRe.Synthetic.preventDefault(event);
            (appReduce(() => AddItem(title)))();
            (reduce(() => ""))();
          }
        )>
        <input
          _type="text"
          id="todo-text-input"
          onChange=(reduce(event => valueFromInputEvent(event)))
          value=title
        />
        <button _type="submit"> (str("Add an item")) </button>
      </form>
  };
};

type state = {items: list(todoItem)};

let component = ReasonReact.reducerComponent("App");

let lastId = ref(0);

let newItem = title => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: false};
};

let make = _children => {
  ...component,
  initialState: () => {
    items: [{id: 0, title: "Initial incomplete item.", completed: false}]
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem(title) => ReasonReact.Update({items: [newItem(title), ...items]})
    | ToggleItem(id) =>
      let items =
        List.map(
          item =>
            item.id === id ? {...item, completed: ! item.completed} : item,
          items
        );
      ReasonReact.Update({items: items});
    },
  render: ({state: {items}, reduce}) => {
    let lengthMessage = itemCount =>
      switch itemCount {
      | 0 => "There are no items in the list. Add some?"
      | 1 => "There is one item in the list. Add more?"
      | _ =>
        "There are "
        ++ string_of_int(itemCount)
        ++ " items in the list. Now that's a crowd!"
      };
    <div>
      <p> (str("This is the App component.")) </p>
      <p> (str(lengthMessage(List.length(items)))) </p>
      <TodoForm appReduce=reduce />
      <h2> (str("Current Items")) </h2>
      <div>
        (
          ReasonReact.arrayToElement(
            Array.of_list(
              List.map(
                item =>
                  <TodoItem
                    item
                    appReduce=reduce
                    key=(string_of_int(item.id))
                  />,
                items
              )
            )
          )
        )
      </div>
    </div>;
  }
};