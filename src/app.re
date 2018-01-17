open TodoApp;

let str = ReasonReact.stringToElement;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    items: [{id: 0, title: "Initial incomplete item.", completed: false}]
  },
  reducer,
  render: ({state, send}) => {
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
      <p> (str(lengthMessage(List.length(state.items)))) </p>
      <TodoForm appSend=send />
      <h2> (str("Current Items")) </h2>
      <TodoList appState=state appSend=send />
    </div>;
  }
};