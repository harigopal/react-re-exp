type todoItem = {
  title: string,
  completed: bool
};

type state = {items: list(todoItem)};

let component = ReasonReact.reducerComponent("App");

let str = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  initialState: () => {
    items: [{title: "Initial uncompleted item.", completed: false}]
  },
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: ({state: {items}}) => {
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
    </div>;
  }
};