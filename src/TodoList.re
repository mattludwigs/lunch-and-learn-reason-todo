type todoItem = string;

type state = {
    todoItems: list(todoItem),
};

type action =
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
    initialState: () => { todoItems: [] },
    reducer: (action, state) => {
        switch (action) {
        | AddTodo(todoItem) => ReasonReact.Update({todoItems: state.todoItems @ [todoItem]})
        | RemoveTodo => ReasonReact.Update(state)
        }
    },
    render: self => {
      <div>
        <h1>{ReasonReact.string("Todo List")}</h1>
        (renderTodoList(self.state.todoItems))
        <button onClick=(_event => self.send(AddTodo("learn reason")))>
          {ReasonReact.string("Add To Do")}
        </button>
      </div>
    }
};

