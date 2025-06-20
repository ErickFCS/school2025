import { createSlice } from "@reduxjs/toolkit";


const signSlice = createSlice({
    initialState: null,
    name: "sign",
    reducers: {
        signIn(_state, action) {
            return action.payload.name
        },
        signOut(_state, _action) {
            return null;
        }
    }
});
export const { signIn, signOut } = signSlice.actions;

const signReducer = signSlice.reducer
export default signReducer;