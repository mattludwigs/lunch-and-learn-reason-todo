type todoItem = string;
type newTodo = string;

type state = {
    todoItems: list(todoItem),
    newTodo: string
};

type action =
  | UpdateNewTodo(newTodo)
  | AddTodo(todoItem)
  | RemoveTodo;

let component = ReasonReact.reducerComponent("TodoList");

let renderTodoItem = (todoItem) => {
    <li>{ReasonReact.string(todoItem)}</li>
};

let renderTodoList = (todos) => {
    <ul>
    {
        todos
        |> List.map(renderTodoItem)
        |> Array.of_list
        |> ReasonReact.array
    }
    </ul>
};

let make = (_children) => {
    ...component,
    initialState: () => { todoItems: [], newTodo: "" },
    reducer: (action, state) => {
        switch (action) {
        | UpdateNewTodo(newTodo) => ReasonReact.Update({ ...state, newTodo: newTodo })
        | AddTodo(todoItem) => ReasonReact.Update({ newTodo: "", todoItems: state.todoItems @ [todoItem]}) 
        | RemoveTodo => ReasonReact.Update(state)
        }
    },
    render: self => {
      <div>
        <h1>{ReasonReact.string("Todo List")}</h1>
        (renderTodoList(self.state.todoItems))
        <input 
            value={self.state.newTodo}
            onChange=(event => self.send(UpdateNewTodo(ReactEvent.Form.target(event)##value)))  />
        <button onClick=(_event => self.send(AddTodo(self.state.newTodo))) >
          {ReasonReact.string("Add To Do")}
        </button>
      </div>
    }
};

