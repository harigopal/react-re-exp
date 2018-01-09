type todoItem = {
  id: int,
  title: string,
  completed: bool
};

let str = ReasonReact.stringToElement;

[@bs.val]
external getElementById : string => Dom.element = "document.getElementById";

type action =
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
      <form
        onSubmit=(
          reduce(event => {
            ReactEventRe.Synthetic.preventDefault(event);
            let title = ReactDOMRe.domElementToObj(
                          getElementById("todo-text-input")
                        )##value;
            AddItem(title);
          })
        )>
        <input _type="text" id="todo-text-input" />
        <button _type="submit"> (str("Add an item")) </button>
      </form>
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